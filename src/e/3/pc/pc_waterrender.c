/* e/3/pc/pc_waterrender.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_waterrender.c:418  [size]
void __cdecl WaterRender_SetModeCallback()
{
  #pragma pack(push, 1)
  union
  {
    struct { int v12; };
    struct { char igi2_o1[16]; char zString[1024]; };
    char igi2_extent[1040];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // esi
  char *ErrorString; // eax
  int v2; // esi
  char *v3; // eax
  int i; // edi
  int v5; // esi
  struct IDirect3DDevice8Vtbl *lpVtbl; // esi
  unsigned int *v7; // eax
  int v8; // esi
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax

  v0 = Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
         Direct3D_ptDevice,
         420000u,
         (Direct3D_isHWVertexShader != 0 ? 0 : 0x10) | 0x208,
         0,
         D3DPOOL_DEFAULT,
         &WaterRender_ptVertexBuffer);
  if ( v0 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    ErrorString = Direct3D_GetErrorString(v0);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      ErrorString,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      438);
    goto LABEL_3;
  }
  v2 = Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
         Direct3D_ptDevice,
         90000u,
         (Direct3D_isHWVertexShader != 0 ? 0 : 0x10) | 0x208,
         D3DFMT_INDEX16,
         D3DPOOL_DEFAULT,
         &WaterRender_ptIndexBuffer);
  if ( v2 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v3 = Direct3D_GetErrorString(v2);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v3,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      447);
    goto LABEL_3;
  }
  for ( i = 0; i < 3; ++i )
  {
    v5 = D3DXAssembleShader(
           (int)WaterRender_azVertexShader[i],
           strlen(WaterRender_azVertexShader[i]),
           0,
           0,
           (int)&WaterRender_ptVertexShaderFunction,
           (int)&WaterRender_ptVertexShaderErrors);
    if ( v5 )
    {
      sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
      v9 = Direct3D_GetErrorString(v5);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        v9,
        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
        458);
      goto LABEL_3;
    }
    if ( WaterRender_ptVertexShaderErrors && !WaterRender_ptVertexShaderFunction )
    {
      v10 = (char *)WaterRender_ptVertexShaderErrors->lpVtbl->GetBufferPointer(WaterRender_ptVertexShaderErrors);
      LDebug_Error("Fatal error in vertex shader:\n%s", v10);
      goto LABEL_3;
    }
    lpVtbl = Direct3D_ptDevice->lpVtbl;
    igi2_frame.v12 = Direct3D_isHWVertexShader != 0 ? 0 : 0x10;
    v7 = (unsigned int *)WaterRender_ptVertexShaderFunction->lpVtbl->GetBufferPointer(WaterRender_ptVertexShaderFunction);
    v8 = lpVtbl->CreateVertexShader(
           Direct3D_ptDevice,
           WaterRender_abVertexLayout,
           v7,
           &WaterRender_anVertexShader[i],
           igi2_frame.v12);
    if ( v8 )
    {
      sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
      v11 = Direct3D_GetErrorString(v8);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        v11,
        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
        471);
LABEL_3:
      abort();
    }
    if ( WaterRender_ptVertexShaderFunction )
    {
      WaterRender_ptVertexShaderFunction->lpVtbl->Release(WaterRender_ptVertexShaderFunction);
      WaterRender_ptVertexShaderFunction = nullptr;
    }
    if ( WaterRender_ptVertexShaderErrors )
    {
      WaterRender_ptVertexShaderErrors->lpVtbl->Release(WaterRender_ptVertexShaderErrors);
      WaterRender_ptVertexShaderErrors = nullptr;
    }
  }
}

// source: e/3/pc/pc_waterrender.c:500  [size]
void __cdecl WaterRender_UnsetModeCallback()
{
  unsigned int *v0; // edi
  int v1; // esi
  char *ErrorString; // eax
  char zString[1024]; // [esp+8h] [ebp-400h] BYREF

  v0 = WaterRender_anVertexShader;
  do
  {
    if ( *v0 )
    {
      v1 = Direct3D_ptDevice->lpVtbl->DeleteVertexShader(Direct3D_ptDevice, *v0);
      if ( v1 )
      {
        sprintf(zString, "Error occured in d3d water renderer");
        ErrorString = Direct3D_GetErrorString(v1);
        LDebug_Error(
          "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
          zString,
          ErrorString,
          "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
          512);
        abort();
      }
    }
    ++v0;
  }
  while ( (int)v0 < 128908748 );
  if ( WaterRender_ptVertexShaderFunction )
    WaterRender_ptVertexShaderFunction->lpVtbl->Release(WaterRender_ptVertexShaderFunction);
  if ( WaterRender_ptVertexShaderErrors )
    WaterRender_ptVertexShaderErrors->lpVtbl->Release(WaterRender_ptVertexShaderErrors);
  if ( WaterRender_ptIndexBuffer )
  {
    WaterRender_ptIndexBuffer->lpVtbl->Release(WaterRender_ptIndexBuffer);
    WaterRender_ptIndexBuffer = nullptr;
  }
  if ( WaterRender_ptVertexBuffer )
  {
    WaterRender_ptVertexBuffer->lpVtbl->Release(WaterRender_ptVertexBuffer);
    WaterRender_ptVertexBuffer = nullptr;
  }
}

// source: e/3/pc/pc_waterrender.c:558  [size]
// attributes: thunk
void __cdecl WaterRender_DestroyCallback()
{
  WaterRender_UnsetModeCallback();
}

// source: e/3/pc/pc_waterrender.c:571  [size]
// attributes: thunk
void __cdecl WaterRender_RestoreCallback()
{
  WaterRender_SetModeCallback();
}

// source: e/3/pc/pc_waterrender.c:584  [size~]
void __cdecl WaterRender_SetTextureState(void *pxContext)
{
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx
  int v2; // esi
  char *v3; // eax
  int v4; // esi
  char *v5; // eax
  int v6; // esi
  char *v7; // eax
  int v8; // esi
  char *v9; // eax
  int v10; // esi
  char *v11; // eax
  int v12; // esi
  char *v13; // eax
  int v14; // esi
  char *v15; // eax
  int v16; // esi
  char *v17; // eax
  int v18; // esi
  char *v19; // eax
  int v20; // esi
  char *v21; // eax
  int v22; // esi
  char *v23; // eax
  int v24; // esi
  char *v25; // eax
  int v26; // esi
  char *v27; // eax
  int v28; // esi
  char *v29; // eax
  int v30; // esi
  char *v31; // eax
  int v32; // esi
  char *v33; // eax
  int v34; // esi
  char *v35; // eax
  int v36; // esi
  char *v37; // eax
  int v38; // esi
  char *v39; // eax
  int v40; // esi
  char *v41; // eax
  int v42; // esi
  char *v43; // eax
  int v44; // esi
  char *v45; // eax
  int v46; // esi
  char *v47; // eax
  int v48; // esi
  char *v49; // eax
  int v50; // esi
  char *v51; // eax
  int v52; // esi
  char *v53; // eax
  struct IDirect3DDevice8Vtbl *v54; // ecx
  int v55; // esi
  char *v56; // eax
  int v57; // esi
  char *v58; // eax
  int v59; // esi
  char *v60; // eax
  int v61; // esi
  char *v62; // eax
  int v63; // esi
  char *ErrorString; // eax
  int v65; // esi
  char *v66; // eax
  int v67; // esi
  char *v68; // eax
  int v69; // esi
  char *v70; // eax
  int v71; // esi
  char *v72; // eax
  int v73; // esi
  char *v74; // eax
  int v75; // esi
  char *v76; // eax
  int v77; // esi
  char *v78; // eax
  int v79; // esi
  char *v80; // eax
  int v81; // esi
  char *v82; // eax
  int v83; // esi
  char *v84; // eax
  int v85; // esi
  char *v86; // eax
  int v87; // esi
  char *v88; // eax
  int v89; // esi
  char *v90; // eax
  int v91; // esi
  char *v92; // eax
  int v93; // esi
  char *v94; // eax
  int v95; // esi
  char *v96; // eax
  int v97; // esi
  char *v98; // eax
  int v99; // esi
  char *v100; // eax
  int v101; // esi
  char *v102; // eax
  int v103; // esi
  char *v104; // eax
  int v105; // esi
  char *v106; // eax
  int v107; // esi
  char *v108; // eax
  int v109; // esi
  char *v110; // eax
  int v111; // esi
  char *v112; // eax
  int v113; // esi
  char *v114; // eax
  int v115; // esi
  char *v116; // eax
  int v117; // esi
  char *v118; // eax
  int v119; // esi
  char *v120; // eax
  int v121; // esi
  char *v122; // eax
  char Buffer[1024]; // [esp+1E0h] [ebp-400h] BYREF

  lpVtbl = Direct3D_ptDevice->lpVtbl;
  if ( WaterRender_iQualityLevel )
  {
    v63 = lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
    if ( v63 )
    {
      sprintf(Buffer, "Error occured in d3d water renderer");
      ErrorString = Direct3D_GetErrorString(v63);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        Buffer,
        ErrorString,
        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
        628);
    }
    else
    {
      v65 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
      if ( v65 )
      {
        sprintf(Buffer, "Error occured in d3d water renderer");
        v66 = Direct3D_GetErrorString(v65);
        LDebug_Error(
          "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
          Buffer,
          v66,
          "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
          629);
      }
      else
      {
        v67 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 3u);
        if ( v67 )
        {
          sprintf(Buffer, "Error occured in d3d water renderer");
          v68 = Direct3D_GetErrorString(v67);
          LDebug_Error(
            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
            Buffer,
            v68,
            "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
            630);
        }
        else
        {
          v69 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 3u);
          if ( v69 )
          {
            sprintf(Buffer, "Error occured in d3d water renderer");
            v70 = Direct3D_GetErrorString(v69);
            LDebug_Error(
              "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
              Buffer,
              v70,
              "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
              631);
          }
          else
          {
            v71 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 1u);
            if ( v71 )
            {
              sprintf(Buffer, "Error occured in d3d water renderer");
              v72 = Direct3D_GetErrorString(v71);
              LDebug_Error(
                "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                Buffer,
                v72,
                "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                632);
            }
            else
            {
              v73 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
              if ( v73 )
              {
                sprintf(Buffer, "Error occured in d3d water renderer");
                v74 = Direct3D_GetErrorString(v73);
                LDebug_Error(
                  "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                  Buffer,
                  v74,
                  "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                  633);
              }
              else
              {
                v75 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 2u);
                if ( v75 )
                {
                  sprintf(Buffer, "Error occured in d3d water renderer");
                  v76 = Direct3D_GetErrorString(v75);
                  LDebug_Error(
                    "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                    Buffer,
                    v76,
                    "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                    634);
                }
                else
                {
                  v77 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 0);
                  if ( v77 )
                  {
                    sprintf(Buffer, "Error occured in d3d water renderer");
                    v78 = Direct3D_GetErrorString(v77);
                    LDebug_Error(
                      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                      Buffer,
                      v78,
                      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                      635);
                  }
                  else
                  {
                    v79 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 2u);
                    if ( v79 )
                    {
                      sprintf(Buffer, "Error occured in d3d water renderer");
                      v80 = Direct3D_GetErrorString(v79);
                      LDebug_Error(
                        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                        Buffer,
                        v80,
                        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                        636);
                    }
                    else
                    {
                      v81 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
                      if ( v81 )
                      {
                        sprintf(Buffer, "Error occured in d3d water renderer");
                        v82 = Direct3D_GetErrorString(v81);
                        LDebug_Error(
                          "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                          Buffer,
                          v82,
                          "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                          641);
                      }
                      else
                      {
                        v83 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 0);
                        if ( v83 )
                        {
                          sprintf(Buffer, "Error occured in d3d water renderer");
                          v84 = Direct3D_GetErrorString(v83);
                          LDebug_Error(
                            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                            Buffer,
                            v84,
                            "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                            642);
                        }
                        else
                        {
                          v85 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                  Direct3D_ptDevice,
                                  0,
                                  D3DTSS_COLORARG2,
                                  2u);
                          if ( v85 )
                          {
                            sprintf(Buffer, "Error occured in d3d water renderer");
                            v86 = Direct3D_GetErrorString(v85);
                            LDebug_Error(
                              "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                              Buffer,
                              v86,
                              "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                              643);
                          }
                          else
                          {
                            v87 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                    Direct3D_ptDevice,
                                    0,
                                    D3DTSS_TEXTURETRANSFORMFLAGS,
                                    0);
                            if ( v87 )
                            {
                              sprintf(Buffer, "Error occured in d3d water renderer");
                              v88 = Direct3D_GetErrorString(v87);
                              LDebug_Error(
                                "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                Buffer,
                                v88,
                                "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                646);
                            }
                            else
                            {
                              v89 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                      Direct3D_ptDevice,
                                      1u,
                                      D3DTSS_TEXCOORDINDEX,
                                      1u);
                              if ( v89 )
                              {
                                sprintf(Buffer, "Error occured in d3d water renderer");
                                v90 = Direct3D_GetErrorString(v89);
                                LDebug_Error(
                                  "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                  Buffer,
                                  v90,
                                  "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                  648);
                              }
                              else
                              {
                                v91 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                        Direct3D_ptDevice,
                                        1u,
                                        D3DTSS_MINFILTER,
                                        2u);
                                if ( v91 )
                                {
                                  sprintf(Buffer, "Error occured in d3d water renderer");
                                  v92 = Direct3D_GetErrorString(v91);
                                  LDebug_Error(
                                    "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                    Buffer,
                                    v92,
                                    "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                    649);
                                }
                                else
                                {
                                  v93 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                          Direct3D_ptDevice,
                                          1u,
                                          D3DTSS_MAGFILTER,
                                          2u);
                                  if ( v93 )
                                  {
                                    sprintf(Buffer, "Error occured in d3d water renderer");
                                    v94 = Direct3D_GetErrorString(v93);
                                    LDebug_Error(
                                      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                      Buffer,
                                      v94,
                                      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                      650);
                                  }
                                  else
                                  {
                                    v95 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                            Direct3D_ptDevice,
                                            1u,
                                            D3DTSS_ADDRESSU,
                                            3u);
                                    if ( v95 )
                                    {
                                      sprintf(Buffer, "Error occured in d3d water renderer");
                                      v96 = Direct3D_GetErrorString(v95);
                                      LDebug_Error(
                                        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                        Buffer,
                                        v96,
                                        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                        651);
                                    }
                                    else
                                    {
                                      v97 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                              Direct3D_ptDevice,
                                              1u,
                                              D3DTSS_ADDRESSV,
                                              3u);
                                      if ( v97 )
                                      {
                                        sprintf(Buffer, "Error occured in d3d water renderer");
                                        v98 = Direct3D_GetErrorString(v97);
                                        LDebug_Error(
                                          "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                          Buffer,
                                          v98,
                                          "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                          652);
                                      }
                                      else
                                      {
                                        v99 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                Direct3D_ptDevice,
                                                1u,
                                                D3DTSS_MIPFILTER,
                                                1u);
                                        if ( v99 )
                                        {
                                          sprintf(Buffer, "Error occured in d3d water renderer");
                                          v100 = Direct3D_GetErrorString(v99);
                                          LDebug_Error(
                                            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                            Buffer,
                                            v100,
                                            "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                            653);
                                        }
                                        else
                                        {
                                          v101 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                   Direct3D_ptDevice,
                                                   1u,
                                                   D3DTSS_TEXCOORDINDEX,
                                                   1u);
                                          if ( v101 )
                                          {
                                            sprintf(Buffer, "Error occured in d3d water renderer");
                                            v102 = Direct3D_GetErrorString(v101);
                                            LDebug_Error(
                                              "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                              Buffer,
                                              v102,
                                              "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                              654);
                                          }
                                          else
                                          {
                                            v103 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                     Direct3D_ptDevice,
                                                     1u,
                                                     D3DTSS_ALPHAOP,
                                                     2u);
                                            if ( v103 )
                                            {
                                              sprintf(Buffer, "Error occured in d3d water renderer");
                                              v104 = Direct3D_GetErrorString(v103);
                                              LDebug_Error(
                                                "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                Buffer,
                                                v104,
                                                "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                655);
                                            }
                                            else
                                            {
                                              v105 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                       Direct3D_ptDevice,
                                                       1u,
                                                       D3DTSS_ALPHAARG1,
                                                       1u);
                                              if ( v105 )
                                              {
                                                sprintf(Buffer, "Error occured in d3d water renderer");
                                                v106 = Direct3D_GetErrorString(v105);
                                                LDebug_Error(
                                                  "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                  Buffer,
                                                  v106,
                                                  "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                  656);
                                              }
                                              else
                                              {
                                                v107 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                         Direct3D_ptDevice,
                                                         1u,
                                                         D3DTSS_ALPHAARG2,
                                                         2u);
                                                if ( v107 )
                                                {
                                                  sprintf(Buffer, "Error occured in d3d water renderer");
                                                  v108 = Direct3D_GetErrorString(v107);
                                                  LDebug_Error(
                                                    "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                    Buffer,
                                                    v108,
                                                    "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                    657);
                                                }
                                                else
                                                {
                                                  v109 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                           Direct3D_ptDevice,
                                                           1u,
                                                           D3DTSS_COLOROP,
                                                           7u);
                                                  if ( v109 )
                                                  {
                                                    sprintf(Buffer, "Error occured in d3d water renderer");
                                                    v110 = Direct3D_GetErrorString(v109);
                                                    LDebug_Error(
                                                      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                      Buffer,
                                                      v110,
                                                      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                      658);
                                                  }
                                                  else
                                                  {
                                                    v111 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                             Direct3D_ptDevice,
                                                             1u,
                                                             D3DTSS_COLORARG1,
                                                             4u);
                                                    if ( v111 )
                                                    {
                                                      sprintf(Buffer, "Error occured in d3d water renderer");
                                                      v112 = Direct3D_GetErrorString(v111);
                                                      LDebug_Error(
                                                        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                        Buffer,
                                                        v112,
                                                        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                        659);
                                                    }
                                                    else
                                                    {
                                                      v113 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                               Direct3D_ptDevice,
                                                               1u,
                                                               D3DTSS_COLORARG2,
                                                               1u);
                                                      if ( v113 )
                                                      {
                                                        sprintf(Buffer, "Error occured in d3d water renderer");
                                                        v114 = Direct3D_GetErrorString(v113);
                                                        LDebug_Error(
                                                          "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                          Buffer,
                                                          v114,
                                                          "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                          660);
                                                      }
                                                      else
                                                      {
                                                        v115 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                                 Direct3D_ptDevice,
                                                                 1u,
                                                                 D3DTSS_TEXTURETRANSFORMFLAGS,
                                                                 0);
                                                        if ( v115 )
                                                        {
                                                          sprintf(Buffer, "Error occured in d3d water renderer");
                                                          v116 = Direct3D_GetErrorString(v115);
                                                          LDebug_Error(
                                                            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                            Buffer,
                                                            v116,
                                                            "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                            661);
                                                        }
                                                        else
                                                        {
                                                          v117 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                                   Direct3D_ptDevice,
                                                                   2u,
                                                                   D3DTSS_COLOROP,
                                                                   1u);
                                                          if ( v117 )
                                                          {
                                                            sprintf(Buffer, "Error occured in d3d water renderer");
                                                            v118 = Direct3D_GetErrorString(v117);
                                                            LDebug_Error(
                                                              "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                              Buffer,
                                                              v118,
                                                              "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                              663);
                                                          }
                                                          else
                                                          {
                                                            v119 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                                     Direct3D_ptDevice,
                                                                     2u,
                                                                     D3DTSS_TEXCOORDINDEX,
                                                                     2u);
                                                            if ( v119 )
                                                            {
                                                              sprintf(Buffer, "Error occured in d3d water renderer");
                                                              v120 = Direct3D_GetErrorString(v119);
                                                              LDebug_Error(
                                                                "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                                Buffer,
                                                                v120,
                                                                "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                                664);
                                                            }
                                                            else
                                                            {
                                                              v121 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                                                       Direct3D_ptDevice,
                                                                       2u,
                                                                       D3DTSS_TEXTURETRANSFORMFLAGS,
                                                                       0);
                                                              if ( !v121 )
                                                                return;
                                                              sprintf(Buffer, "Error occured in d3d water renderer");
                                                              v122 = Direct3D_GetErrorString(v121);
                                                              LDebug_Error(
                                                                "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                                                                Buffer,
                                                                v122,
                                                                "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                                                                665);
                                                            }
                                                          }
                                                        }
                                                      }
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
LABEL_4:
    abort();
  }
  v2 = lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
  if ( v2 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v3 = Direct3D_GetErrorString(v2);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v3,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      587);
    goto LABEL_4;
  }
  v4 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
  if ( v4 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v5 = Direct3D_GetErrorString(v4);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v5,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      588);
    goto LABEL_4;
  }
  v6 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  if ( v6 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v7 = Direct3D_GetErrorString(v6);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v7,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      589);
    goto LABEL_4;
  }
  v8 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  if ( v8 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v9 = Direct3D_GetErrorString(v8);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v9,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      590);
    goto LABEL_4;
  }
  v10 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 1u);
  if ( v10 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v11 = Direct3D_GetErrorString(v10);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v11,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      591);
    goto LABEL_4;
  }
  v12 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  if ( v12 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v13 = Direct3D_GetErrorString(v12);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v13,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      592);
    goto LABEL_4;
  }
  v14 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
  if ( v14 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v15 = Direct3D_GetErrorString(v14);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v15,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      593);
    goto LABEL_4;
  }
  v16 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  if ( v16 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v17 = Direct3D_GetErrorString(v16);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v17,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      594);
    goto LABEL_4;
  }
  v18 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  if ( v18 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v19 = Direct3D_GetErrorString(v18);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v19,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      595);
    goto LABEL_4;
  }
  v20 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
  if ( v20 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v21 = Direct3D_GetErrorString(v20);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v21,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      596);
    goto LABEL_4;
  }
  v22 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  if ( v22 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v23 = Direct3D_GetErrorString(v22);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v23,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      597);
    goto LABEL_4;
  }
  v24 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  if ( v24 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v25 = Direct3D_GetErrorString(v24);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v25,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      598);
    goto LABEL_4;
  }
  v26 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  if ( v26 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v27 = Direct3D_GetErrorString(v26);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v27,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      599);
    goto LABEL_4;
  }
  v28 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_MINFILTER, 2u);
  if ( v28 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v29 = Direct3D_GetErrorString(v28);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v29,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      601);
    goto LABEL_4;
  }
  v30 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_MAGFILTER, 2u);
  if ( v30 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v31 = Direct3D_GetErrorString(v30);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v31,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      602);
    goto LABEL_4;
  }
  v32 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ADDRESSU, 3u);
  if ( v32 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v33 = Direct3D_GetErrorString(v32);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v33,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      603);
    goto LABEL_4;
  }
  v34 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ADDRESSV, 3u);
  if ( v34 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v35 = Direct3D_GetErrorString(v34);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v35,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      604);
    goto LABEL_4;
  }
  v36 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_MIPFILTER, 1u);
  if ( v36 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v37 = Direct3D_GetErrorString(v36);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v37,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      605);
    goto LABEL_4;
  }
  v38 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_TEXCOORDINDEX, 1u);
  if ( v38 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v39 = Direct3D_GetErrorString(v38);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v39,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      606);
    goto LABEL_4;
  }
  v40 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAOP, 3u);
  if ( v40 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v41 = Direct3D_GetErrorString(v40);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v41,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      607);
    goto LABEL_4;
  }
  v42 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAARG1, 2u);
  if ( v42 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v43 = Direct3D_GetErrorString(v42);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v43,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      608);
    goto LABEL_4;
  }
  v44 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAARG2, 1u);
  if ( v44 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v45 = Direct3D_GetErrorString(v44);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v45,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      609);
    goto LABEL_4;
  }
  v46 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 7u);
  if ( v46 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v47 = Direct3D_GetErrorString(v46);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v47,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      610);
    goto LABEL_4;
  }
  v48 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG1, 2u);
  if ( v48 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v49 = Direct3D_GetErrorString(v48);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v49,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      611);
    goto LABEL_4;
  }
  v50 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG2, 4u);
  if ( v50 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v51 = Direct3D_GetErrorString(v50);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v51,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      612);
    goto LABEL_4;
  }
  v52 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  if ( v52 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v53 = Direct3D_GetErrorString(v52);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v53,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      613);
    goto LABEL_4;
  }
  v54 = Direct3D_ptDevice->lpVtbl;
  if ( !WaterRender_isAboveWater )
  {
    v61 = v54->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
    if ( !v61 )
      return;
    sprintf(Buffer, "Error occured in d3d water renderer");
    v62 = Direct3D_GetErrorString(v61);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v62,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      623);
    goto LABEL_4;
  }
  v55 = v54->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLOROP, 1u);
  if ( v55 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v56 = Direct3D_GetErrorString(v55);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v56,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      617);
    goto LABEL_4;
  }
  v57 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_TEXCOORDINDEX, 2u);
  if ( v57 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v58 = Direct3D_GetErrorString(v57);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v58,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      618);
    goto LABEL_4;
  }
  v59 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  if ( v59 )
  {
    sprintf(Buffer, "Error occured in d3d water renderer");
    v60 = Direct3D_GetErrorString(v59);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      Buffer,
      v60,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      619);
    goto LABEL_4;
  }
}

// source: e/3/pc/pc_waterrender.c:675  [size]
void __cdecl WaterRender_SetGenericState(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct _D3DMATERIAL8 tMaterial; };
    struct { char igi2_o1[68]; char zString[1024]; };
    char igi2_extent[1092];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  char *ErrorString; // eax
  int v3; // esi
  char *v4; // eax
  int v5; // esi
  char *v6; // eax
  int v7; // esi
  char *v8; // eax
  int v9; // esi
  char *v10; // eax
  int v11; // esi
  char *v12; // eax
  int v13; // esi
  char *v14; // eax
  int v15; // esi
  char *v16; // eax
  int v17; // esi
  char *v18; // eax
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx
  int v20; // esi
  char *v21; // eax
  int v22; // esi
  char *v23; // eax
  int v24; // esi
  char *v25; // eax
  int v26; // esi
  char *v27; // eax
  int v28; // esi
  char *v29; // eax
  int v30; // esi
  char *v31; // eax
  int v32; // esi
  char *v33; // eax
  int v34; // esi
  char *v35; // eax
  int v36; // esi
  char *v37; // eax

  memset(&igi2_frame.tMaterial, 0, sizeof(igi2_frame.tMaterial));
  igi2_frame.tMaterial.Diffuse.r = 1.0;
  igi2_frame.tMaterial.Diffuse.g = 1.0;
  igi2_frame.tMaterial.Diffuse.b = 1.0;
  igi2_frame.tMaterial.Ambient.r = 1.0;
  igi2_frame.tMaterial.Ambient.g = 1.0;
  igi2_frame.tMaterial.Ambient.b = 1.0;
  v1 = Direct3D_ptDevice->lpVtbl->SetMaterial(Direct3D_ptDevice, &igi2_frame.tMaterial);
  if ( v1 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    ErrorString = Direct3D_GetErrorString(v1);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      ErrorString,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      693);
    goto LABEL_3;
  }
  v3 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 1u);
  if ( v3 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v4 = Direct3D_GetErrorString(v3);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v4,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      696);
    goto LABEL_3;
  }
  v5 = Direct3D_ptDevice->lpVtbl->SetRenderState(
         Direct3D_ptDevice,
         D3DRS_FOGCOLOR,
         (__int64)(Mesh3D_atFogColor[1].vZ * 255.0)
       - (((unsigned int)(__int64)(Mesh3D_atFogColor[1].vY * -255.0)
         + ((unsigned int)(__int64)(Mesh3D_atFogColor[1].vX * -255.0) << 8)) << 8));
  if ( v5 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v6 = Direct3D_GetErrorString(v5);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v6,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      700);
    goto LABEL_3;
  }
  v7 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, LODWORD(Mesh3D_avFogDensity[1]));
  if ( v7 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v8 = Direct3D_GetErrorString(v7);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v8,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      701);
    goto LABEL_3;
  }
  v9 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  if ( v9 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v10 = Direct3D_GetErrorString(v9);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v10,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      702);
    goto LABEL_3;
  }
  v11 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 1u);
  if ( v11 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v12 = Direct3D_GetErrorString(v11);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v12,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      703);
    goto LABEL_3;
  }
  v13 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  if ( v13 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v14 = Direct3D_GetErrorString(v13);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v14,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      704);
    goto LABEL_3;
  }
  v15 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  if ( v15 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v16 = Direct3D_GetErrorString(v15);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v16,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      706);
    goto LABEL_3;
  }
  v17 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARMATERIALSOURCE, 2u);
  if ( v17 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v18 = Direct3D_GetErrorString(v17);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v18,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      707);
    goto LABEL_3;
  }
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  if ( WaterRender_isAboveWater )
  {
    v20 = lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 2u);
    if ( v20 )
    {
      sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
      v21 = Direct3D_GetErrorString(v20);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        v21,
        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
        710);
      goto LABEL_3;
    }
  }
  else
  {
    v22 = lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
    if ( v22 )
    {
      sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
      v23 = Direct3D_GetErrorString(v22);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        v23,
        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
        714);
      goto LABEL_3;
    }
  }
  v24 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  if ( v24 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v25 = Direct3D_GetErrorString(v24);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v25,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      716);
    goto LABEL_3;
  }
  v26 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  if ( v26 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v27 = Direct3D_GetErrorString(v26);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v27,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      717);
    goto LABEL_3;
  }
  v28 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  if ( v28 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v29 = Direct3D_GetErrorString(v28);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v29,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      718);
    goto LABEL_3;
  }
  v30 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  if ( v30 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v31 = Direct3D_GetErrorString(v30);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v31,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      719);
    goto LABEL_3;
  }
  v32 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  if ( v32 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v33 = Direct3D_GetErrorString(v32);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v33,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      720);
    goto LABEL_3;
  }
  v34 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  if ( v34 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v35 = Direct3D_GetErrorString(v34);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v35,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      721);
    goto LABEL_3;
  }
  v36 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  if ( v36 )
  {
    sprintf(igi2_frame.zString, "Error occured in d3d water renderer");
    v37 = Direct3D_GetErrorString(v36);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v37,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      723);
LABEL_3:
    abort();
  }
}

// source: e/3/pc/pc_waterrender.c:732  [size]
void __cdecl WaterRender_SetBlendState(void *pxContext)
{
  int v1; // esi
  char *ErrorString; // eax
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx
  int v4; // esi
  char *v5; // eax
  int v6; // esi
  char *v7; // eax
  int v8; // esi
  char *v9; // eax
  int v10; // esi
  char *v11; // eax
  char zString[1024]; // [esp+24h] [ebp-400h] BYREF

  v1 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
  if ( v1 )
  {
    sprintf(zString, "Error occured in d3d water renderer");
    ErrorString = Direct3D_GetErrorString(v1);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      zString,
      ErrorString,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      736);
    goto LABEL_3;
  }
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  if ( WaterRender_iQualityLevel <= 0 )
  {
    v8 = lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
    if ( v8 )
    {
      sprintf(zString, "Error occured in d3d water renderer");
      v9 = Direct3D_GetErrorString(v8);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        zString,
        v9,
        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
        744);
    }
    else
    {
      v10 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
      if ( !v10 )
        return;
      sprintf(zString, "Error occured in d3d water renderer");
      v11 = Direct3D_GetErrorString(v10);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        zString,
        v11,
        "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
        745);
    }
LABEL_3:
    abort();
  }
  v4 = lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 2u);
  if ( v4 )
  {
    sprintf(zString, "Error occured in d3d water renderer");
    v5 = Direct3D_GetErrorString(v4);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      zString,
      v5,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      739);
    goto LABEL_3;
  }
  v6 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 5u);
  if ( v6 )
  {
    sprintf(zString, "Error occured in d3d water renderer");
    v7 = Direct3D_GetErrorString(v6);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      zString,
      v7,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      740);
    goto LABEL_3;
  }
}

// source: e/3/pc/pc_waterrender.c:763  [size~]
void __cdecl WaterRender_CalculateRenderVertex(
        struct WaterRenderVertex_t *ptDest,
        struct WaterRenderVertex_t *ptDest0,
        struct WaterRenderVertex_t *ptDest1,
        struct WaterRenderManualVertex_t *ptSource,
        struct WaterRenderManualVertex_t *ptSource0,
        struct WaterRenderManualVertex_t *ptSource1,
        float vT,
        struct WaterContext_t *ptContext)
{
  double v8; // st7
  double v9; // st6
  double v10; // st5
  double v11; // st4
  double v12; // st5
  double v13; // rt0
  double v14; // st7
  double v15; // st7
  double v16; // st6
  double v17; // st5
  BOOL v18; // esi
  double v19; // st6
  BOOL v20; // edx
  BOOL v21; // ecx
  unsigned int v22; // eax
  float v23; // [esp+4h] [ebp-10h]
  float v24; // [esp+8h] [ebp-Ch]
  float v25; // [esp+10h] [ebp-4h]
  float v26; // [esp+10h] [ebp-4h]
  float ptDest1a = *(float *)&vT; // [esp+20h] [ebp+Ch] ARGSLOT

  v8 = WaterRender_vNormalScale * ptDest->tNormal.vX;
  ptDest->tNormal.vX = v8;
  v9 = WaterRender_vNormalScale * ptDest->tNormal.vY;
  ptDest->tNormal.vY = v9;
  v23 = WaterRender_vNormalScale * ptDest->tNormal.vZ;
  ptDest->tNormal.vZ = v23;
  if ( vT < 1.0 )
  {
    v10 = (ptDest0->tPos.vX + ptDest1->tPos.vX) * 0.5;
    v11 = (ptDest0->tPos.vY + ptDest1->tPos.vY) * 0.5;
    v25 = (ptDest0->tPos.vZ + ptDest1->tPos.vZ) * 0.5;
    ptDest->tPos.vX = (ptDest->tPos.vX - v10) * vT + v10;
    ptDest->tPos.vY = (ptDest->tPos.vY - v11) * vT + v11;
    ptDest->tPos.vZ = (ptDest->tPos.vZ - v25) * vT + v25;
    v12 = (ptDest0->tNormal.vX + ptDest1->tNormal.vX) * 0.5;
    v26 = (ptDest0->tNormal.vZ + ptDest1->tNormal.vZ) * 0.5;
    v13 = (ptDest0->tNormal.vY + ptDest1->tNormal.vY) * 0.5;
    ptDest->tNormal.vX = (v8 - v12) * vT + v12;
    ptDest->tNormal.vY = (v9 - v13) * vT + v13;
    ptDest->tNormal.vZ = (v23 - v26) * vT + v26;
    v14 = (ptDest0->vDelta + ptDest1->vDelta) * 0.5;
    ptDest->vDelta = (ptDest->vDelta - v14) * vT + v14;
  }
  v24 = TransContext_tActiveTransContext.tMatrix.tX.vZ * ptDest->tPos.vZ
      + TransContext_tActiveTransContext.tMatrix.tX.vY * ptDest->tPos.vY
      + TransContext_tActiveTransContext.tMatrix.tX.vX * ptDest->tPos.vX;
  v15 = TransContext_tActiveTransContext.tMatrix.tY.vZ * ptDest->tPos.vZ
      + TransContext_tActiveTransContext.tMatrix.tY.vY * ptDest->tPos.vY
      + TransContext_tActiveTransContext.tMatrix.tY.vX * ptDest->tPos.vX;
  v16 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * ptDest->tPos.vZ
      + TransContext_tActiveTransContext.tMatrix.tZ.vY * ptDest->tPos.vY
      + TransContext_tActiveTransContext.tMatrix.tZ.vX * ptDest->tPos.vX;
  if ( v16 < Direct3D_vWorldMinZ )
  {
    ptSource->bOutcode = 16;
  }
  else
  {
    v17 = TransContext_tActiveTransContext.vFOVX * v16;
    v18 = -v17 > v24;
    v19 = v16 * TransContext_tActiveTransContext.vFOVY;
    v20 = v15 < -v19;
    ptDest1a = v17;
    v21 = v24 > (double)ptDest1a;
    if ( v15 <= v19 )
      v22 = v18 | (2 * (v20 | (2 * v21)));
    else
      v22 = v18 | (2 * (v20 | (2 * (v21 | 2))));
    ptSource->bOutcode = v22;
  }
}

// source: e/3/pc/pc_waterrender.c:836  [size~]
void __cdecl WaterRender_Draw(struct WaterContext_t *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v137; };
    struct { float v138; };
    struct { float v139; };
    struct { float v140; };
    struct { float v141; };
    struct { char igi2_o5[4]; float v142; };
    struct { char igi2_o6[4]; float v143; };
    struct { char igi2_o7[4]; float v144; };
    struct { char igi2_o8[4]; float v145; };
    struct { char igi2_o9[4]; float v146; };
    struct { char igi2_o10[8]; float v147; };
    struct { char igi2_o11[12]; int v148; };
    struct { char igi2_o12[12]; struct WaterRenderVertex_t *v149; };
    struct { char igi2_o13[12]; float v150; };
    struct { char igi2_o14[12]; float v151; };
    struct { char igi2_o15[40]; int v152; };
    struct { char igi2_o16[40]; int v153; };
    struct { char igi2_o17[40]; unsigned __int16 v154; };
    struct { char igi2_o18[40]; struct real32x3_t *v155; };
    struct { char igi2_o19[44]; float v156; };
    struct { char igi2_o20[44]; unsigned __int16 v157; };
    struct { char igi2_o21[44]; int v158; };
    struct { char igi2_o22[48]; unsigned __int16 v159; };
    struct { char igi2_o23[48]; struct WaterRenderVertex_t *v160; };
    struct { char igi2_o24[52]; float v161; };
    struct { char igi2_o25[56]; int v162; };
    struct { char igi2_o26[60]; float v163; };
    struct { char igi2_o27[64]; float v164; };
    struct { char igi2_o28[68]; float v165; };
    struct { char igi2_o29[72]; struct WaterRenderVertex_t *v166; };
    struct { char igi2_o30[76]; struct WaterRenderVertex_t *ptDest; };
    struct { char igi2_o31[80]; struct WaterRenderVertex_t *v168; };
    struct { char igi2_o32[84]; struct WaterRenderVertex_t *v169; };
    struct { char igi2_o33[88]; float v170; };
    struct { char igi2_o34[92]; float vX; };
    struct { char igi2_o35[96]; float v172; };
    struct { char igi2_o36[100]; float v173; };
    struct { char igi2_o37[104]; int v174; };
    struct { char igi2_o38[108]; struct WaterRenderVertex_t *ptDest0; };
    struct { char igi2_o39[112]; float v176; };
    struct { char igi2_o40[116]; float v177; };
    struct { char igi2_o41[120]; float v178; };
    struct { char igi2_o42[124]; int v179; };
    struct { char igi2_o43[128]; unsigned __int16 v180; };
    struct { char igi2_o44[130]; unsigned __int16 v181; };
    struct { char igi2_o45[132]; float v182; };
    struct { char igi2_o46[136]; float v183; };
    struct { char igi2_o47[140]; _WORD v184[4]; };
    struct { char igi2_o48[148]; struct WaterRenderVertex_t *ptDest1; };
    struct { char igi2_o49[152]; float v186; };
    struct { char igi2_o50[156]; float v187; };
    struct { char igi2_o51[160]; int v188; };
    struct { char igi2_o52[164]; int v189; };
    struct { char igi2_o53[168]; float v190; };
    struct { char igi2_o54[172]; int v191; };
    struct { char igi2_o55[176]; float v192; };
    struct { char igi2_o56[180]; float v193; };
    struct { char igi2_o57[184]; float v194; };
    struct { char igi2_o58[188]; float v195; };
    struct { char igi2_o59[192]; float v196[4]; };
    struct { char igi2_o60[208]; struct real32x3_t v197; };
    struct { char igi2_o61[220]; int v198; };
    struct { char igi2_o62[224]; struct real32x3_t tFrontColor; };
    struct { char igi2_o63[236]; int v200; };
    struct { char igi2_o64[240]; struct real32x3_t v201; };
    struct { char igi2_o65[252]; int v202; };
    struct { char igi2_o66[256]; _DWORD v203[4]; };
    struct { char igi2_o67[272]; _DWORD v204[4]; };
    struct { char igi2_o68[288]; float v205; };
    struct { char igi2_o69[292]; float vEnvScale; };
    struct { char igi2_o70[296]; int v207; };
    struct { char igi2_o71[300]; int v208; };
    struct { char igi2_o72[304]; _DWORD v209[4]; };
    struct { char igi2_o73[320]; int v210[16]; };
    struct { char igi2_o74[384]; int v211[16]; };
    struct { char igi2_o75[448]; int v212[16]; };
    struct { char igi2_o76[512]; char Buffer[1024]; };
    struct { char igi2_o77[1536]; int v214[16]; };
    char igi2_extent[1600];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vY; // edx
  float vZ; // eax
  int v3; // esi
  struct Envmap_t *ptEnvmap; // eax
  struct IDirect3DIndexBuffer8Vtbl *lpVtbl; // ecx
  double v6; // st7
  double v7; // st6
  int v8; // edi
  int v9; // eax
  int v10; // ebx
  double v11; // st7
  double v12; // st6
  float *v13; // eax
  double v14; // st5
  float v15; // ecx
  char v16; // cl
  struct WaterRenderManualVertex_t *v17; // edi
  double v18; // st7
  struct WaterRenderVertex_t *v19; // ecx
  double v20; // st6
  unsigned int bOutcode; // edx
  unsigned int v22; // esi
  int v23; // ecx
  int v24; // eax
  int v25; // eax
  unsigned __int16 v26; // ax
  struct WaterRenderVertex_t *v27; // eax
  float *v28; // edi
  float *v29; // edx
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st6
  double v34; // st5
  double v35; // st4
  double v36; // st6
  double v37; // st7
  float *v38; // edx
  double v39; // st7
  int v40; // eax
  int v41; // edi
  struct WaterRenderVertex_t *v42; // eax
  double vDistance; // st7
  unsigned __int16 v44; // dx
  struct WaterRenderVertex_t *v45; // esi
  float v46; // edx
  double v47; // st7
  struct WaterRenderVertex_t *v48; // ebx
  struct WaterRenderVertex_t *v49; // eax
  float v50; // edx
  struct WaterRenderManualVertex_t *v51; // edi
  unsigned int v52; // edx
  int v53; // eax
  int v54; // eax
  unsigned int v55; // edx
  int v56; // eax
  int v57; // eax
  unsigned __int16 v58; // ax
  struct WaterRenderVertex_t *v59; // esi
  struct WaterRenderVertex_t *v60; // ecx
  double v61; // st7
  struct WaterRenderVertex_t *v62; // esi
  int v63; // edi
  struct WaterRenderVertex_t *v64; // ebx
  float v65; // edx
  bool v66; // cc
  int v67; // kr00_4
  unsigned int v68; // esi
  int v69; // eax
  unsigned __int16 v70; // di
  float v71; // eax
  int v72; // eax
  unsigned __int16 v73; // si
  int v74; // eax
  int v75; // edi
  struct WaterRenderVertex_t *v76; // ecx
  double v77; // st7
  struct WaterRenderVertex_t *v78; // esi
  float v79; // eax
  double v80; // st7
  struct WaterRenderVertex_t *v81; // ecx
  struct WaterRenderVertex_t *v82; // edx
  int v83; // ebx
  unsigned __int16 v84; // dx
  unsigned __int16 v85; // si
  int v86; // eax
  int v87; // edi
  _WORD *v88; // esi
  unsigned __int16 v89; // ax
  int v90; // esi
  struct RenderStateBlock_t *v91; // edx
  int v92; // ebx
  int v93; // esi
  char *ErrorString; // eax
  struct RenderStateBlock_t *v95; // eax
  int v96; // ecx
  struct RenderStateBlock_t *v97; // eax
  int v98; // ecx
  struct RenderStateBlock_t *v99; // eax
  int v100; // ecx
  struct RenderStateBlock_t *v101; // eax
  int v102; // ecx
  float vScaledUVScale; // ecx
  double v104; // st7
  float v105; // eax
  float v106; // edx
  float v107; // ecx
  float v108; // edx
  int v109; // esi
  char *v110; // eax
  int v111; // esi
  char *v112; // eax
  int v113; // esi
  char *v114; // eax
  int v115; // esi
  char *v116; // eax
  int v117; // esi
  char *v118; // eax
  struct real32x3_t *ptDiffuseColor; // eax
  struct real32x3_t *ptSpecularColor; // eax
  int v121; // esi
  char *v122; // eax
  int v123; // esi
  char *v124; // eax
  int v125; // esi
  char *v126; // eax
  int v127; // esi
  char *v128; // eax
  int v129; // esi
  char *v130; // eax
  int v131; // esi
  char *v132; // eax
  signed int v133; // esi
  struct TexInfo_s **aptTexInfo; // edi
  struct IDirect3DBaseTexture8 *ptDirect3DBaseTexture; // eax
  char *v136; // eax

  vY = ptContext->tDisplacement.vY;
  vZ = ptContext->tDisplacement.vZ;
  igi2_frame.vX = ptContext->tDisplacement.vX;
  v3 = 0;
  igi2_frame.v172 = vY;
  igi2_frame.v173 = vZ;
  if ( WaterRender_iQualityLevel <= 0 )
  {
    igi2_frame.v191 = 0;
  }
  else
  {
    ptEnvmap = ptContext->ptEnvmap;
    if ( !ptEnvmap->isValid )
      return;
    igi2_frame.v191 = WaterRender_iQualityLevel + (ptEnvmap->eEnvmapType == ENVMAP_TYPE_CUBIC);
  }
  igi2_frame.v170 = -igi2_frame.v173;
  igi2_frame.v142 = -igi2_frame.v172;
  igi2_frame.v137 = -igi2_frame.vX;
  ((void (__cdecl *)(int *, float *, float *, _DWORD, _DWORD, _DWORD, _DWORD))ptContext->pfWaterFunction)(
    &igi2_frame.v162,
    &igi2_frame.v161,
    igi2_frame.v196,
    LODWORD(igi2_frame.v137),
    LODWORD(igi2_frame.v142),
    LODWORD(igi2_frame.v170),
    0);
  if ( *(float *)&igi2_frame.v162 >= 0.0 )
  {
    WaterRender_isAboveWater = 0;
    WaterRender_vNormalScale = -1.0;
  }
  else
  {
    WaterRender_isAboveWater = 1;
    WaterRender_vNormalScale = 1.0;
  }
  lpVtbl = WaterRender_ptIndexBuffer->lpVtbl;
  WaterRender_nNumStackItems = 0;
  WaterRender_nNumVertices = 0;
  WaterRender_nNumIndices = 0;
  v6 = 1.0 / (1.0 - Direct3D_vD3DMinZ / Direct3D_vD3DMaxZ);
  v7 = Direct3D_vMaxZ - Direct3D_vMinZ;
  WaterRender_vScaleZ = -(Direct3D_vInverseScale * v7 * Direct3D_vD3DMinZ * v6);
  WaterRender_vOffsetZ = v7 * v6 + Direct3D_vMinZ;
  if ( !lpVtbl->Lock(WaterRender_ptIndexBuffer, 0, 0, (unsigned __int8 **)&igi2_frame.v189, 0x2000u) )
  {
    v10 = WaterRender_nNumVertices;
    do
    {
      igi2_frame.v162 = 2 * (v3 & 1) - 1;
      v11 = (double)igi2_frame.v162 * ptContext->vRadius;
      igi2_frame.v162 = (v3 & 2) - 1;
      v12 = (double)igi2_frame.v162 * ptContext->vRadius + igi2_frame.v172;
      v13 = &flt_7B0D298[7 * v10];
      v14 = v11 + igi2_frame.vX;
      v15 = igi2_frame.v170;
      *v13 = v14;
      v13[1] = v12;
      igi2_frame.v143 = v12 - igi2_frame.v172;
      igi2_frame.v138 = v14 - igi2_frame.vX;
      ((void (__cdecl *)(float *, float *, float *, _DWORD, _DWORD, _DWORD, _DWORD))ptContext->pfWaterFunction)(
        v13 + 2,
        v13 + 6,
        v13 + 3,
        LODWORD(igi2_frame.v138),
        LODWORD(igi2_frame.v143),
        LODWORD(v15),
        LODWORD(WaterRender_atManualVertex[v10].vDistance));
      v10 = WaterRender_nNumVertices + 1;
      ++v3;
      ++WaterRender_nNumVertices;
    }
    while ( v3 < 4 );
    v16 = 0;
    igi2_frame.v152 = 0;
    igi2_frame.v166 = (struct WaterRenderVertex_t *)flt_7B0D298;
    v17 = WaterRender_atManualVertex;
    igi2_frame.v183 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * igi2_frame.v173;
    do
    {
      igi2_frame.v162 = 2 * (v16 & 1) - 1;
      v18 = (double)igi2_frame.v162 * ptContext->vRadius;
      igi2_frame.v162 = (v16 & 2) - 1;
      v19 = igi2_frame.v166;
      v20 = (double)igi2_frame.v162 * ptContext->vRadius;
      *(float *)&igi2_frame.ptDest1 = v18 + igi2_frame.vX;
      v17->vDistance = TransContext_tActiveTransContext.tMatrix.tZ.vY * (v20 + igi2_frame.v172)
                     + TransContext_tActiveTransContext.tMatrix.tZ.vX * *(float *)&igi2_frame.ptDest1
                     + igi2_frame.v183;
      WaterRender_CalculateRenderVertex(v19, nullptr, nullptr, v17, nullptr, nullptr, 1.0, ptContext);
      v16 = igi2_frame.v152 + 1;
      ++v17;
      ++igi2_frame.v152;
      ++igi2_frame.v166;
    }
    while ( (int)v17 < 128908784 );
    bOutcode = WaterRender_atManualVertex[2].bOutcode;
    v22 = WaterRender_atManualVertex[1].bOutcode;
    v23 = WaterRender_nNumStackItems;
    if ( (WaterRender_atManualVertex[0].bOutcode
        & WaterRender_atManualVertex[1].bOutcode
        & WaterRender_atManualVertex[2].bOutcode) == 0 )
    {
      v24 = WaterRender_nNumStackItems;
      WaterRender_atDrawStack[v24].aiVertex[0] = 0;
      ++v23;
      WaterRender_atDrawStack[v24].aiVertex[1] = 1;
      WaterRender_atDrawStack[v24].aiVertex[2] = 2;
      WaterRender_nNumStackItems = v23;
    }
    if ( (bOutcode & WaterRender_atManualVertex[3].bOutcode & v22) == 0 )
    {
      v25 = v23;
      WaterRender_atDrawStack[v25].aiVertex[0] = 3;
      ++v23;
      WaterRender_atDrawStack[v25].aiVertex[1] = 2;
      WaterRender_atDrawStack[v25].aiVertex[2] = 1;
      WaterRender_nNumStackItems = v23;
    }
    if ( v23 )
    {
LABEL_20:
      v26 = WaterRender_atDrawStack[--v23].aiVertex[0];
      WaterRender_nNumStackItems = v23;
      igi2_frame.v159 = v26;
      LODWORD(igi2_frame.v192) = 28 * v26 + 129028760;
      LODWORD(igi2_frame.v161) = WaterRender_atDrawStack[v23].aiVertex[1];
      igi2_frame.v169 = (struct WaterRenderVertex_t *)LODWORD(igi2_frame.v161);
      LODWORD(igi2_frame.v193) = 28 * LODWORD(igi2_frame.v161) + 129028760;
      LODWORD(igi2_frame.v165) = WaterRender_atDrawStack[v23].aiVertex[2];
      *(float *)&igi2_frame.v168 = igi2_frame.v165;
      LODWORD(igi2_frame.v194) = 28 * LODWORD(igi2_frame.v165) + 129028760;
      v27 = nullptr;
      igi2_frame.v153 = 0;
      igi2_frame.v156 = 0.0;
      while ( 1 )
      {
        igi2_frame.ptDest = (struct WaterRenderVertex_t *)((char *)&v27->tPos.vX + 1);
        v28 = *((float **)&igi2_frame.v192 + LODWORD(igi2_frame.v156));
        v29 = *((float **)&igi2_frame.v192 + ((int)&v27->tPos.vX + 1) % 3);
        igi2_frame.v176 = *v29 - *v28;
        igi2_frame.v177 = v29[1] - v28[1];
        v30 = v29[2] - v28[2];
        igi2_frame.v178 = v30;
        igi2_frame.v164 = igi2_frame.v176 * igi2_frame.v176 + igi2_frame.v177 * igi2_frame.v177 + v30 * v30;
        v31 = (igi2_frame.v177 * v28[1] + igi2_frame.v178 * v28[2] + igi2_frame.v176 * *v28) * (-1.0 / igi2_frame.v164);
        igi2_frame.v163 = v31;
        if ( v31 >= 0.0 )
        {
          if ( igi2_frame.v163 <= 1.0 )
          {
            igi2_frame.v178 = igi2_frame.v163 * igi2_frame.v178;
            igi2_frame.v176 = igi2_frame.v163 * igi2_frame.v176 + *v28;
            igi2_frame.v177 = igi2_frame.v163 * igi2_frame.v177 + v28[1];
            v32 = igi2_frame.v178 + v28[2];
            v33 = igi2_frame.v177;
            v34 = igi2_frame.v176;
          }
          else
          {
            v32 = v29[2];
            v33 = v29[1];
            v34 = *v29;
          }
        }
        else
        {
          v32 = v28[2];
          v33 = v28[1];
          v34 = *v28;
        }
        v35 = v34 * v34 + v33 * v33 + v32 * v32;
        v36 = (1.0 - (v29[5] * v28[5] + v29[4] * v28[4] + v29[3] * v28[3]) * 0.0) * ptContext->vDetail;
        igi2_frame.v163 = v36 * v36 * v35;
        if ( igi2_frame.v164 <= (double)igi2_frame.v163 || igi2_frame.v164 <= 4194304.0 )
        {
          igi2_frame.v196[LODWORD(igi2_frame.v156)] = 0.0;
          igi2_frame.v183 = igi2_frame.v156;
        }
        else
        {
          v37 = igi2_frame.v164 / igi2_frame.v163;
          ++igi2_frame.v153;
          v38 = (float *)(&igi2_frame.ptDest1 + LODWORD(igi2_frame.v156));
          LODWORD(igi2_frame.v196[LODWORD(igi2_frame.v156)]) = 1;
          igi2_frame.v190 = igi2_frame.v156;
          v39 = (v37 - 1.0) * 0.30000001192092896;
          *v38 = v39;
          if ( v39 > 1.0 )
            v39 = 1.0;
          *v38 = v39;
        }
        v27 = igi2_frame.ptDest;
        igi2_frame.v156 = *(float *)&igi2_frame.ptDest;
        if ( (int)igi2_frame.ptDest >= 3 )
        {
          switch ( igi2_frame.v153 )
          {
            case 0:
              if ( (WaterRender_atManualVertex[(_DWORD)igi2_frame.v169].bOutcode
                  & WaterRender_atManualVertex[igi2_frame.v159].bOutcode
                  & WaterRender_atManualVertex[(_DWORD)igi2_frame.v168].bOutcode) == 0 )
              {
                v40 = WaterRender_nNumIndices;
                *(_WORD *)(igi2_frame.v189 + 2 * WaterRender_nNumIndices) = igi2_frame.v159;
                ++v40;
                *(_WORD *)(igi2_frame.v189 + 2 * v40++) = WaterRender_atDrawStack[v23].aiVertex[1];
                *(_WORD *)(igi2_frame.v189 + 2 * v40) = WaterRender_atDrawStack[v23].aiVertex[2];
                WaterRender_nNumIndices = v40 + 1;
              }
              goto LABEL_65;
            case 1:
              igi2_frame.v154 = WaterRender_atDrawStack[v23].aiVertex[LODWORD(igi2_frame.v190)];
              igi2_frame.v164 = *(float *)&v10;
              v41 = (unsigned __int16)v10;
              v42 = (struct WaterRenderVertex_t *)WaterRender_atDrawStack[v23].aiVertex[(LODWORD(igi2_frame.v190) + 1) % 3];
              igi2_frame.ptDest = v42;
              vDistance = WaterRender_atManualVertex[igi2_frame.v154].vDistance;
              igi2_frame.v169 = v42;
              *(float *)&igi2_frame.v168 = (vDistance + WaterRender_atManualVertex[(_DWORD)v42].vDistance) * 0.5;
              v44 = WaterRender_atDrawStack[v23].aiVertex[(LODWORD(igi2_frame.v190) + 2) % 3];
              WaterRender_atManualVertex[(unsigned __int16)v10].vDistance = *(float *)&igi2_frame.v168;
              v45 = (struct WaterRenderVertex_t *)(28 * (unsigned __int16)v10 + 129028760);
              igi2_frame.v157 = v44;
              LODWORD(v46) = 8 * (_DWORD)v42 + 128908756;
              v42 = (struct WaterRenderVertex_t *)(28 * (_DWORD)v42);
              WaterRender_nNumVertices = v10 + 1;
              v47 = flt_7B0D298[7 * igi2_frame.v154] + v42[4608170].tPos.vX;
              LODWORD(igi2_frame.v165) = 8 * igi2_frame.v154 + 128908756;
              v48 = (struct WaterRenderVertex_t *)((int)flt_7B0D298 + (_DWORD)v42);
              v49 = (struct WaterRenderVertex_t *)&flt_7B0D298[7 * igi2_frame.v154];
              igi2_frame.ptDest0 = v49;
              igi2_frame.v161 = v46;
              v50 = igi2_frame.v170;
              v45->tPos.vX = v47 * 0.5;
              v45->tPos.vY = (v49->tPos.vY + v48->tPos.vY) * 0.5;
              igi2_frame.v149 = igi2_frame.v168;
              v45->tPos.vZ = (v49->tPos.vZ + v48->tPos.vZ) * 0.5;
              igi2_frame.v144 = v45->tPos.vY - igi2_frame.v172;
              igi2_frame.v139 = v45->tPos.vX - igi2_frame.vX;
              ((void (__cdecl *)(float *, float *, struct real32x3_t *, _DWORD, _DWORD, _DWORD, struct WaterRenderVertex_t *))ptContext->pfWaterFunction)(
                &v45->tPos.vZ,
                &v45->vDelta,
                &v45->tNormal,
                LODWORD(igi2_frame.v139),
                LODWORD(igi2_frame.v144),
                LODWORD(v50),
                igi2_frame.v149);
              LODWORD(igi2_frame.v163) = 8 * (_DWORD)igi2_frame.v169 + 128908752;
              v51 = (struct WaterRenderManualVertex_t *)(8 * v41 + 128908752);
              WaterRender_CalculateRenderVertex(
                v45,
                igi2_frame.ptDest0,
                v48,
                v51,
                (struct WaterRenderManualVertex_t *)(8 * igi2_frame.v154 + 128908752),
                (struct WaterRenderManualVertex_t *)LODWORD(igi2_frame.v163),
                *((float *)&igi2_frame.ptDest1 + LODWORD(igi2_frame.v190)),
                ptContext);
              if ( *(float *)LODWORD(igi2_frame.v165) >= (double)*(float *)LODWORD(igi2_frame.v161) )
              {
                v55 = v51->bOutcode & WaterRender_atManualVertex[igi2_frame.v157].bOutcode;
                v23 = WaterRender_nNumStackItems;
                if ( (v55 & *(_DWORD *)LODWORD(igi2_frame.v163)) == 0 )
                {
                  v56 = WaterRender_nNumStackItems;
                  WaterRender_atDrawStack[v56].aiVertex[0] = (unsigned __int16)igi2_frame.ptDest;
                  WaterRender_atDrawStack[v56].aiVertex[1] = igi2_frame.v157;
                  ++v23;
                  WaterRender_atDrawStack[v56].aiVertex[2] = LOWORD(igi2_frame.v164);
                  WaterRender_nNumStackItems = v23;
                }
                if ( (v55 & WaterRender_atManualVertex[igi2_frame.v154].bOutcode) == 0 )
                {
                  v57 = v23;
                  WaterRender_atDrawStack[v57].aiVertex[0] = igi2_frame.v157;
                  WaterRender_atDrawStack[v57].aiVertex[1] = igi2_frame.v154;
                  WaterRender_atDrawStack[v57].aiVertex[2] = LOWORD(igi2_frame.v164);
                  ++v23;
                  goto LABEL_63;
                }
              }
              else
              {
                v52 = v51->bOutcode & WaterRender_atManualVertex[igi2_frame.v157].bOutcode;
                v23 = WaterRender_nNumStackItems;
                if ( (v52 & WaterRender_atManualVertex[igi2_frame.v154].bOutcode) == 0 )
                {
                  v53 = WaterRender_nNumStackItems;
                  WaterRender_atDrawStack[v53].aiVertex[0] = igi2_frame.v157;
                  WaterRender_atDrawStack[v53].aiVertex[1] = igi2_frame.v154;
                  ++v23;
                  WaterRender_atDrawStack[v53].aiVertex[2] = LOWORD(igi2_frame.v164);
                  WaterRender_nNumStackItems = v23;
                }
                if ( (v52 & *(_DWORD *)LODWORD(igi2_frame.v163)) == 0 )
                {
                  v54 = v23;
                  WaterRender_atDrawStack[v54].aiVertex[0] = (unsigned __int16)igi2_frame.ptDest;
                  WaterRender_atDrawStack[v54].aiVertex[1] = igi2_frame.v157;
                  WaterRender_atDrawStack[v54].aiVertex[2] = LOWORD(igi2_frame.v164);
                  ++v23;
                  goto LABEL_63;
                }
              }
              goto LABEL_64;
            case 2:
              igi2_frame.v158 = 0;
              v58 = WaterRender_atDrawStack[v23].aiVertex[(LODWORD(igi2_frame.v183) + 1) % 3];
              LODWORD(igi2_frame.tFrontColor.vX) = (LODWORD(igi2_frame.v183) + 1) % 3;
              LOWORD(igi2_frame.v166) = v58;
              HIWORD(igi2_frame.v166) = WaterRender_atDrawStack[v23].aiVertex[LODWORD(igi2_frame.v183)];
              v59 = (struct WaterRenderVertex_t *)WaterRender_atDrawStack[v23].aiVertex[(LODWORD(igi2_frame.v183) + 2) % 3];
              LODWORD(igi2_frame.tFrontColor.vY) = (LODWORD(igi2_frame.v183) + 2) % 3;
              LODWORD(igi2_frame.v161) = 8 * (unsigned __int16)v59 + 128908756;
              igi2_frame.v168 = v59;
              igi2_frame.v160 = (struct WaterRenderVertex_t *)&flt_7B0D298[7 * (unsigned __int16)v59];
              igi2_frame.ptDest = (struct WaterRenderVertex_t *)(8 * (unsigned __int16)v59 + 128908752);
              igi2_frame.v155 = &igi2_frame.tFrontColor;
              while ( 1 )
              {
                v60 = (struct WaterRenderVertex_t *)*(unsigned __int16 *)((char *)&igi2_frame.v166 + igi2_frame.v158);
                v61 = WaterRender_atManualVertex[(_DWORD)v60].vDistance + *(float *)LODWORD(igi2_frame.v161);
                igi2_frame.ptDest0 = v60;
                v62 = (struct WaterRenderVertex_t *)(28 * (unsigned __int16)v10 + 129028760);
                *(_WORD *)((char *)&igi2_frame.v162 + igi2_frame.v158) = v10;
                v63 = *(unsigned __int16 *)((char *)&igi2_frame.v162 + igi2_frame.v158);
                WaterRender_nNumVertices = v10 + 1;
                v64 = (struct WaterRenderVertex_t *)&flt_7B0D298[7 * (_DWORD)v60];
                v63 *= 8;
                igi2_frame.v165 = v61 * 0.5;
                v65 = igi2_frame.v170;
                *(float *)(v63 + 128908756) = igi2_frame.v165;
                v62->tPos.vX = (igi2_frame.v160->tPos.vX + v64->tPos.vX) * 0.5;
                v62->tPos.vY = (v64->tPos.vY + igi2_frame.v160->tPos.vY) * 0.5;
                igi2_frame.v150 = igi2_frame.v165;
                v62->tPos.vZ = (v64->tPos.vZ + igi2_frame.v160->tPos.vZ) * 0.5;
                igi2_frame.v145 = v62->tPos.vY - igi2_frame.v172;
                igi2_frame.v140 = v62->tPos.vX - igi2_frame.vX;
                ((void (__cdecl *)(float *, float *, struct real32x3_t *, _DWORD, _DWORD, _DWORD, _DWORD))ptContext->pfWaterFunction)(
                  &v62->tPos.vZ,
                  &v62->vDelta,
                  &v62->tNormal,
                  LODWORD(igi2_frame.v140),
                  LODWORD(igi2_frame.v145),
                  LODWORD(v65),
                  LODWORD(igi2_frame.v150));
                WaterRender_CalculateRenderVertex(
                  v62,
                  igi2_frame.v160,
                  v64,
                  (struct WaterRenderManualVertex_t *)((char *)WaterRender_atManualVertex + v63),
                  (struct WaterRenderManualVertex_t *)igi2_frame.ptDest,
                  (struct WaterRenderManualVertex_t *)(8 * (_DWORD)igi2_frame.ptDest0 + 128908752),
                  *((float *)&igi2_frame.ptDest1 + LODWORD(igi2_frame.v155->vX)),
                  ptContext);
                v66 = igi2_frame.v158 + 2 < 4;
                igi2_frame.v155 = (struct real32x3_t *)((char *)igi2_frame.v155 + 4);
                igi2_frame.v158 += 2;
                if ( !v66 )
                  break;
                v10 = WaterRender_nNumVertices;
              }
              v67 = igi2_frame.v162;
              v68 = WaterRender_atManualVertex[(unsigned __int16)igi2_frame.v162].bOutcode
                  & WaterRender_atManualVertex[HIWORD(igi2_frame.v162)].bOutcode;
              igi2_frame.v165 = *(float *)&WaterRender_atManualVertex[(unsigned __int16)igi2_frame.v162].bOutcode;
              v23 = WaterRender_nNumStackItems;
              if ( (v68 & LODWORD(igi2_frame.ptDest->tPos.vX)) == 0 )
              {
                v69 = WaterRender_nNumStackItems;
                WaterRender_atDrawStack[v69].aiVertex[0] = (unsigned __int16)igi2_frame.v168;
                ++v23;
                WaterRender_atDrawStack[v69].aiVertex[1] = HIWORD(v67);
                WaterRender_atDrawStack[v69].aiVertex[2] = v67;
                WaterRender_nNumStackItems = v23;
              }
              v70 = HIWORD(igi2_frame.v166);
              igi2_frame.v161 = *(float *)&WaterRender_atManualVertex[HIWORD(igi2_frame.v166)].bOutcode;
              v71 = igi2_frame.v161;
              if ( (LODWORD(igi2_frame.v161) & v68) == 0 )
              {
                v72 = v23;
                WaterRender_atDrawStack[v72].aiVertex[0] = v67;
                WaterRender_atDrawStack[v72].aiVertex[1] = HIWORD(v67);
                ++v23;
                WaterRender_atDrawStack[v72].aiVertex[2] = v70;
                v71 = igi2_frame.v161;
                WaterRender_nNumStackItems = v23;
              }
              v73 = (unsigned __int16)igi2_frame.v166;
              if ( (LODWORD(v71) & WaterRender_atManualVertex[(unsigned __int16)igi2_frame.v166].bOutcode & LODWORD(igi2_frame.v165)) != 0 )
                goto LABEL_64;
              v74 = v23;
              WaterRender_atDrawStack[v74].aiVertex[0] = v67;
              WaterRender_atDrawStack[v74].aiVertex[1] = v70;
              WaterRender_atDrawStack[v74].aiVertex[2] = v73;
              ++v23;
LABEL_63:
              WaterRender_nNumStackItems = v23;
LABEL_64:
              v10 = WaterRender_nNumVertices;
LABEL_65:
              if ( !v23 )
                goto LABEL_66;
              goto LABEL_20;
            case 3:
              igi2_frame.v184[0] = igi2_frame.v159;
              igi2_frame.v184[1] = LOWORD(igi2_frame.v161);
              igi2_frame.v184[2] = LOWORD(igi2_frame.v165);
              v75 = 0;
              while ( 1 )
              {
                v76 = (struct WaterRenderVertex_t *)(unsigned __int16)igi2_frame.v184[v75];
                v77 = WaterRender_atManualVertex[(_DWORD)v76].vDistance;
                v78 = (struct WaterRenderVertex_t *)(28 * (unsigned __int16)v10 + 129028760);
                igi2_frame.ptDest0 = v76;
                LODWORD(v79) = (unsigned __int16)igi2_frame.v184[(v75 + 1) % 3];
                igi2_frame.v165 = v79;
                *(&igi2_frame.v180 + v75) = v10;
                v80 = v77 + WaterRender_atManualVertex[LODWORD(v79)].vDistance;
                WaterRender_nNumVertices = v10 + 1;
                v81 = (struct WaterRenderVertex_t *)&flt_7B0D298[7 * (_DWORD)v76];
                v82 = (struct WaterRenderVertex_t *)&flt_7B0D298[7 * LODWORD(v79)];
                v83 = *(&igi2_frame.v180 + v75);
                igi2_frame.v169 = v81;
                igi2_frame.v161 = v80 * 0.5;
                igi2_frame.v168 = v82;
                *(float *)(v83 * 8 + 128908756) = igi2_frame.v161;
                LODWORD(igi2_frame.v196[v75]) = v78;
                v78->tPos.vX = (v81->tPos.vX + v82->tPos.vX) * 0.5;
                v78->tPos.vY = (v81->tPos.vY + v82->tPos.vY) * 0.5;
                igi2_frame.v151 = igi2_frame.v161;
                igi2_frame.v147 = igi2_frame.v170;
                v78->tPos.vZ = (v81->tPos.vZ + v82->tPos.vZ) * 0.5;
                igi2_frame.v146 = v78->tPos.vY - igi2_frame.v172;
                igi2_frame.v141 = v78->tPos.vX - igi2_frame.vX;
                ((void (__cdecl *)(float *, float *, struct real32x3_t *, _DWORD, _DWORD, _DWORD, _DWORD))ptContext->pfWaterFunction)(
                  &v78->tPos.vZ,
                  &v78->vDelta,
                  &v78->tNormal,
                  LODWORD(igi2_frame.v141),
                  LODWORD(igi2_frame.v146),
                  LODWORD(igi2_frame.v147),
                  LODWORD(igi2_frame.v151));
                WaterRender_CalculateRenderVertex(
                  v78,
                  igi2_frame.v169,
                  igi2_frame.v168,
                  &WaterRender_atManualVertex[v83],
                  (struct WaterRenderManualVertex_t *)(8 * (_DWORD)igi2_frame.ptDest0 + 128908752),
                  (struct WaterRenderManualVertex_t *)(8 * LODWORD(igi2_frame.v165) + 128908752),
                  *((float *)&igi2_frame.ptDest1 + v75++),
                  ptContext);
                if ( v75 >= 3 )
                  break;
                v10 = WaterRender_nNumVertices;
              }
              v84 = LOWORD(igi2_frame.v182);
              v85 = igi2_frame.v181;
              v23 = WaterRender_nNumStackItems;
              if ( (WaterRender_atManualVertex[igi2_frame.v181].bOutcode
                  & WaterRender_atManualVertex[LOWORD(igi2_frame.v182)].bOutcode
                  & WaterRender_atManualVertex[igi2_frame.v180].bOutcode) == 0 )
              {
                v86 = WaterRender_nNumStackItems;
                WaterRender_atDrawStack[v86].aiVertex[0] = igi2_frame.v180;
                ++v23;
                WaterRender_atDrawStack[v86].aiVertex[1] = v85;
                WaterRender_atDrawStack[v86].aiVertex[2] = v84;
                WaterRender_nNumStackItems = v23;
              }
              v87 = 0;
              v88 = (_WORD *)(6 * v23 + 128884714);
              do
              {
                v89 = *(&igi2_frame.v180 + (v87 + 2) % 3);
                if ( (WaterRender_atManualVertex[(unsigned __int16)igi2_frame.v184[v87]].bOutcode
                    & WaterRender_atManualVertex[v89].bOutcode
                    & WaterRender_atManualVertex[*(&igi2_frame.v180 + v87)].bOutcode) == 0 )
                {
                  *(v88 - 1) = igi2_frame.v184[v87];
                  *v88 = *(&igi2_frame.v180 + v87);
                  v88[1] = v89;
                  ++v23;
                  v88 += 3;
                }
                ++v87;
              }
              while ( v87 < 3 );
              goto LABEL_63;
            default:
              goto LABEL_65;
          }
        }
      }
    }
LABEL_66:
    v90 = WaterRender_ptIndexBuffer->lpVtbl->Unlock(WaterRender_ptIndexBuffer);
    if ( v90 )
    {
      sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
      igi2_frame.v148 = 1388;
    }
    else
    {
      if ( WaterRender_ptVertexBuffer->lpVtbl->Lock(
             WaterRender_ptVertexBuffer,
             0,
             28 * WaterRender_nNumVertices,
             (unsigned __int8 **)&igi2_frame.v161,
             0x2000u) )
      {
        return;
      }
      qmemcpy((void *)LODWORD(igi2_frame.v161), flt_7B0D298, 28 * WaterRender_nNumVertices);
      v90 = WaterRender_ptVertexBuffer->lpVtbl->Unlock(WaterRender_ptVertexBuffer);
      if ( v90 )
      {
        sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
        igi2_frame.v148 = 1409;
      }
      else
      {
        if ( !WaterRender_nNumIndices )
          return;
        v91 = Direct3D_ptGenericStateBlock;
        v92 = Direct3D_isHWVertexShader;
        Direct3D_ptTextureStateBlock->eCurrentState = -1;
        v91->eCurrentState = -1;
        v93 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SOFTWAREVERTEXPROCESSING, v92 == 0);
        if ( v93 )
        {
          sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
          ErrorString = Direct3D_GetErrorString(v93);
          LDebug_Error(
            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
            igi2_frame.Buffer,
            ErrorString,
            "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
            1422);
          goto LABEL_74;
        }
        v95 = Direct3D_ptTextureStateBlock;
        v96 = WaterRender_eTextureState;
        if ( Direct3D_ptTextureStateBlock->eCurrentState != WaterRender_eTextureState )
        {
          Direct3D_ptTextureStateBlock->eCurrentState = WaterRender_eTextureState;
          v95->atRenderState[v96].pfCallback(nullptr);
        }
        v97 = Direct3D_ptBlendStateBlock;
        v98 = WaterRender_eBlendState;
        if ( Direct3D_ptBlendStateBlock->eCurrentState != WaterRender_eBlendState )
        {
          Direct3D_ptBlendStateBlock->eCurrentState = WaterRender_eBlendState;
          v97->atRenderState[v98].pfCallback(nullptr);
        }
        v99 = Direct3D_ptGenericStateBlock;
        v100 = WaterRender_eGenericState;
        if ( Direct3D_ptGenericStateBlock->eCurrentState != WaterRender_eGenericState )
        {
          Direct3D_ptGenericStateBlock->eCurrentState = WaterRender_eGenericState;
          v99->atRenderState[v100].pfCallback(nullptr);
        }
        v101 = Direct3D_ptClippingStateBlock;
        v102 = Direct3D_eClippingStateOn;
        if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
        {
          Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
          v101->atRenderState[v102].pfCallback(nullptr);
        }
        vScaledUVScale = ptContext->vScaledUVScale;
        v104 = ptContext->vAlpha + 1.0;
        igi2_frame.vEnvScale = ptContext->vEnvScale;
        v105 = ptContext->tDisplacement.vX;
        igi2_frame.v196[0] = v104;
        igi2_frame.v205 = igi2_frame.vEnvScale;
        v106 = vScaledUVScale;
        igi2_frame.vX = v105;
        *(float *)igi2_frame.v204 = vScaledUVScale;
        v107 = ptContext->tDisplacement.vY;
        *(float *)&igi2_frame.v204[1] = v106;
        v108 = ptContext->tDisplacement.vZ;
        igi2_frame.v209[0] = 1017567517;
        igi2_frame.v209[1] = 1065011511;
        igi2_frame.v209[3] = 1065353216;
        igi2_frame.v176 = 0.0;
        igi2_frame.v177 = 0.5;
        igi2_frame.v178 = 1.0;
        igi2_frame.v179 = 0x40000000;
        memset(&igi2_frame.v196[1], 0, 12);
        igi2_frame.v207 = 0;
        igi2_frame.v208 = 0;
        igi2_frame.v203[0] = 1056964608;
        igi2_frame.v203[1] = 1056964608;
        igi2_frame.v203[2] = 0;
        igi2_frame.v203[3] = 1065353216;
        igi2_frame.v204[2] = 0;
        igi2_frame.v204[3] = 1065353216;
        igi2_frame.v172 = v107;
        igi2_frame.v173 = v108;
        igi2_frame.v174 = 0;
        if ( WaterRender_iQualityLevel > 0 )
          igi2_frame.v196[0] = -ptContext->vAlpha;
        igi2_frame.v209[2] = LODWORD(ptContext->vMaxReflectionAngle);
        memset(igi2_frame.v211, 0, sizeof(igi2_frame.v211));
        *(float *)&igi2_frame.v211[5] = Direct3D_vScale;
        *(float *)&igi2_frame.v211[10] = Direct3D_vScale;
        *(float *)igi2_frame.v211 = Direct3D_vScale;
        igi2_frame.v211[15] = 1065353216;
        v109 = Direct3D_ptDevice->lpVtbl->GetTransform(Direct3D_ptDevice, D3DTS_VIEW, (struct _D3DMATRIX *)igi2_frame.v212);
        if ( v109 )
        {
          sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
          v110 = Direct3D_GetErrorString(v109);
          LDebug_Error(
            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
            igi2_frame.Buffer,
            v110,
            "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
            1463);
          goto LABEL_74;
        }
        v90 = Direct3D_ptDevice->lpVtbl->GetTransform(Direct3D_ptDevice, D3DTS_PROJECTION, (struct _D3DMATRIX *)igi2_frame.v214);
        if ( v90 )
        {
          sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
          igi2_frame.v148 = 1464;
        }
        else
        {
          v111 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 15u, igi2_frame.v212, 4u);
          if ( v111 )
          {
            sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
            v112 = Direct3D_GetErrorString(v111);
            LDebug_Error(
              "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
              igi2_frame.Buffer,
              v112,
              "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
              1465);
            goto LABEL_74;
          }
          D3DXMatrixMultiply((int)igi2_frame.v210, (int)igi2_frame.v211, (int)igi2_frame.v212);
          D3DXMatrixMultiply((int)igi2_frame.v210, (int)igi2_frame.v210, (int)igi2_frame.v214);
          D3DXMatrixTranspose((int)igi2_frame.v210, (int)igi2_frame.v210);
          igi2_frame.v192 = *(float *)&igi2_frame.v210[12] * DrawTerrainMesh_vFogDensity;
          igi2_frame.v193 = *(float *)&igi2_frame.v210[13] * DrawTerrainMesh_vFogDensity;
          igi2_frame.v194 = *(float *)&igi2_frame.v210[14] * DrawTerrainMesh_vFogDensity;
          igi2_frame.v195 = *(float *)&igi2_frame.v210[15] * DrawTerrainMesh_vFogDensity;
          v113 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 0, igi2_frame.v210, 4u);
          if ( v113 )
          {
            sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
            v114 = Direct3D_GetErrorString(v113);
            LDebug_Error(
              "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
              igi2_frame.Buffer,
              v114,
              "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
              1483);
            goto LABEL_74;
          }
          v90 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 4u, &igi2_frame.v192, 1u);
          if ( v90 )
          {
            sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
            igi2_frame.v148 = 1484;
          }
          else
          {
            v115 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 5u, &igi2_frame.v176, 1u);
            if ( v115 )
            {
              sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
              v116 = Direct3D_GetErrorString(v115);
              LDebug_Error(
                "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                igi2_frame.Buffer,
                v116,
                "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                1487);
              goto LABEL_74;
            }
            v90 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 6u, igi2_frame.v196, 1u);
            if ( v90 )
            {
              sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
              igi2_frame.v148 = 1488;
            }
            else
            {
              v117 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 7u, &igi2_frame.vX, 1u);
              if ( v117 )
              {
                sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                v118 = Direct3D_GetErrorString(v117);
                LDebug_Error(
                  "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                  igi2_frame.Buffer,
                  v118,
                  "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                  1491);
                goto LABEL_74;
              }
              if ( SkyDome_ptDirlight )
              {
                igi2_frame.ptDest1 = (struct WaterRenderVertex_t *)LODWORD(SkyDome_ptDirlight->tDir.vX);
                igi2_frame.v186 = SkyDome_ptDirlight->tDir.vY;
                igi2_frame.v187 = SkyDome_ptDirlight->tDir.vZ;
                igi2_frame.v188 = 0;
                igi2_frame.tFrontColor = SkyDome_ptDirlight->tFrontColor;
                ptDiffuseColor = ptContext->ptDiffuseColor;
                igi2_frame.v200 = 0;
                igi2_frame.v201 = *ptDiffuseColor;
                ptSpecularColor = ptContext->ptSpecularColor;
                igi2_frame.v202 = 0;
                igi2_frame.v197 = *ptSpecularColor;
                igi2_frame.v198 = 0;
                v121 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 8u, &igi2_frame.ptDest1, 1u);
                if ( v121 )
                {
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  v122 = Direct3D_GetErrorString(v121);
                  LDebug_Error(
                    "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                    igi2_frame.Buffer,
                    v122,
                    "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                    1511);
                  goto LABEL_74;
                }
                v90 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 9u, &igi2_frame.tFrontColor, 1u);
                if ( v90 )
                {
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  igi2_frame.v148 = 1512;
                  goto LABEL_134;
                }
                v123 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 20u, &igi2_frame.v201, 1u);
                if ( v123 )
                {
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  v124 = Direct3D_GetErrorString(v123);
                  LDebug_Error(
                    "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                    igi2_frame.Buffer,
                    v124,
                    "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                    1513);
                  goto LABEL_74;
                }
                v90 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 21u, &igi2_frame.v197, 1u);
                if ( v90 )
                {
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  igi2_frame.v148 = 1514;
                  goto LABEL_134;
                }
              }
              else
              {
                *(float *)&igi2_frame.ptDest1 = 0.0;
                igi2_frame.v186 = 0.0;
                igi2_frame.v187 = 0.0;
                igi2_frame.v188 = 0;
                v125 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 8u, &igi2_frame.ptDest1, 1u);
                if ( v125 )
                {
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  v126 = Direct3D_GetErrorString(v125);
                  LDebug_Error(
                    "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                    igi2_frame.Buffer,
                    v126,
                    "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                    1521);
                  goto LABEL_74;
                }
                v90 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 9u, &igi2_frame.ptDest1, 1u);
                if ( v90 )
                {
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  igi2_frame.v148 = 1522;
                  goto LABEL_134;
                }
              }
              igi2_frame.v197 = Mesh3D_atAmbientColor[1];
              igi2_frame.v198 = 0;
              v127 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 10u, &igi2_frame.v197, 1u);
              if ( v127 )
              {
                sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                v128 = Direct3D_GetErrorString(v127);
                LDebug_Error(
                  "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                  igi2_frame.Buffer,
                  v128,
                  "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                  1529);
                goto LABEL_74;
              }
              v90 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 11u, &igi2_frame.v205, 1u);
              if ( v90 )
              {
                sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                igi2_frame.v148 = 1533;
              }
              else
              {
                v129 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 12u, igi2_frame.v203, 1u);
                if ( v129 )
                {
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  v130 = Direct3D_GetErrorString(v129);
                  LDebug_Error(
                    "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                    igi2_frame.Buffer,
                    v130,
                    "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                    1534);
                  goto LABEL_74;
                }
                v90 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 13u, igi2_frame.v204, 1u);
                if ( v90 )
                {
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  igi2_frame.v148 = 1535;
                }
                else
                {
                  v131 = Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 14u, igi2_frame.v209, 1u);
                  if ( v131 )
                  {
                    sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                    v132 = Direct3D_GetErrorString(v131);
                    LDebug_Error(
                      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                      igi2_frame.Buffer,
                      v132,
                      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
                      1536);
                    goto LABEL_74;
                  }
                  if ( WaterRender_iQualityLevel )
                  {
                    Direct3D_SetTexture(0, (struct IDirect3DBaseTexture8 *)ptContext->ptEnvmap->ptCubemap);
                  }
                  else
                  {
                    v133 = 0;
                    aptTexInfo = ptContext->aptTexInfo;
                    do
                    {
                      if ( *aptTexInfo )
                        ptDirect3DBaseTexture = (*aptTexInfo)->ptDirect3DBaseTexture;
                      else
                        ptDirect3DBaseTexture = nullptr;
                      Direct3D_SetTexture(v133++, ptDirect3DBaseTexture);
                      ++aptTexInfo;
                    }
                    while ( v133 < 2 );
                  }
                  Direct3D_SetStreamSource(0, WaterRender_ptVertexBuffer, 0x1Cu);
                  Direct3D_SetIndices(WaterRender_ptIndexBuffer, 0);
                  Direct3D_SetVertexShader(WaterRender_anVertexShader[igi2_frame.v191]);
                  Direct3D_DrawIndexedPrimitive(
                    D3DPT_TRIANGLELIST,
                    0,
                    WaterRender_nNumVertices,
                    0,
                    WaterRender_nNumIndices / 3);
                  v90 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SOFTWAREVERTEXPROCESSING, 0);
                  if ( !v90 )
                    return;
                  sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
                  igi2_frame.v148 = 1598;
                }
              }
            }
          }
        }
      }
    }
LABEL_134:
    v9 = v90;
    goto LABEL_135;
  }
  v8 = WaterRender_ptVertexBuffer->lpVtbl->Unlock(WaterRender_ptVertexBuffer);
  if ( v8 )
  {
    sprintf(igi2_frame.Buffer, "Error occured in d3d water renderer");
    igi2_frame.v148 = 949;
    v9 = v8;
LABEL_135:
    v136 = Direct3D_GetErrorString(v9);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.Buffer,
      v136,
      "\\project\\igi2\\E\\3\\pc\\pc_waterrender.c",
      igi2_frame.v148);
LABEL_74:
    abort();
  }
}

// source: e/3/pc/pc_waterrender.c:1607  [size]
int __cdecl WaterRender_GetQualityLevel()
{
  return WaterRender_iQualityLevel;
}

// source: e/3/pc/pc_waterrender.c:1619  [size]
int __cdecl WaterRender_SetQualityLevel(int iRequestedLevel)
{
  int result; // eax
  enum bool aisCapable[3]; // [esp+0h] [ebp-Ch]

  aisCapable[2] = false;
  aisCapable[0] = true;
  aisCapable[1] = Direct3D_tCaps.TextureCaps & 0x800;
  for ( result = 2; result >= 0; --result )
  {
    if ( aisCapable[result] )
      break;
  }
  WaterRender_iQualityLevel = iRequestedLevel;
  if ( iRequestedLevel >= result )
    WaterRender_iQualityLevel = result;
  return result;
}

// source: e/3/pc/pc_waterrender.c:1659  [size]
int __cdecl WaterRender_GetHighestSupportedQualityLevel()
{
  int v0; // esi
  int v1; // edi

  v0 = WaterRender_iQualityLevel;
  v1 = WaterRender_SetQualityLevel(3);
  WaterRender_SetQualityLevel(v0);
  return v1;
}

// source: e/3/pc/pc_waterrender.c:1679  [size]
void __cdecl WaterRender_Open()
{
  int v0; // eax
  struct RenderStateBlock_t *v1; // ecx
  int nNumStates; // eax
  struct RenderStateBlock_t *v3; // ecx
  int v4; // eax
  struct RenderStateBlock_t *v5; // ecx
  int v6; // eax

  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawWater");
      abort();
    }
  }
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[v0] = (void (__cdecl *)(void *))WaterRender_Draw;
  v1 = Direct3D_ptTextureStateBlock;
  RenderMode_atRenderModeMethod[v0].zName = "DrawWater";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  WaterRender_eDrawWaterMethod = v0;
  nNumStates = v1->nNumStates;
  v1->nNumStates = nNumStates + 1;
  v1->atRenderState[nNumStates].pfCallback = WaterRender_SetTextureState;
  v3 = Direct3D_ptBlendStateBlock;
  WaterRender_eTextureState = nNumStates;
  v4 = Direct3D_ptBlendStateBlock->nNumStates;
  Direct3D_ptBlendStateBlock->nNumStates = v4 + 1;
  v3->atRenderState[v4].pfCallback = WaterRender_SetBlendState;
  v5 = Direct3D_ptGenericStateBlock;
  WaterRender_eBlendState = v4;
  v6 = Direct3D_ptGenericStateBlock->nNumStates;
  Direct3D_ptGenericStateBlock->nNumStates = v6 + 1;
  v5->atRenderState[v6].pfCallback = WaterRender_SetGenericState;
  WaterRender_eGenericState = v6;
  Direct3D_RegisterCallback(WaterRender_SetModeCallback, &Direct3D_ptSetModeCallback);
  Direct3D_RegisterCallback(WaterRender_UnsetModeCallback, &Direct3D_ptUnsetModeCallback);
  Direct3D_RegisterCallback(WaterRender_RestoreCallback, &Direct3D_ptRestoreCallback);
  Direct3D_RegisterCallback(WaterRender_DestroyCallback, &Direct3D_ptDestroyCallback);
}

// source: e/3/pc/pc_waterrender.c:1706  [size]
void __cdecl WaterRender_Close()
{
  Direct3D_ptTextureStateBlock->atRenderState[WaterRender_eTextureState].pfCallback = nullptr;
  Direct3D_ptBlendStateBlock->atRenderState[WaterRender_eBlendState].pfCallback = nullptr;
  Direct3D_ptGenericStateBlock->atRenderState[WaterRender_eGenericState].pfCallback = nullptr;
  RenderMode_atRenderModeMethod[WaterRender_eDrawWaterMethod].isAllocated = 0;
}

// source: e/3/pc/pc_waterrender.c:1725  [size]
int __cdecl WaterRender_GetDrawWaterMethod()
{
  return WaterRender_eDrawWaterMethod;
}
