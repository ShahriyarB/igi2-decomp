/* b/4/tga.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/tga.c:52  [anchor-hash]
unsigned __int8 __cdecl TGA_GetByte(struct File_s *ptFile)
{
  return TGA_pnFile[TGA_nFilePos++];
}

// source: b/4/tga.c:67  [size]
unsigned int *__cdecl TGA_PutPixel(
        unsigned int *pValue,
        unsigned int r,
        unsigned int g,
        unsigned int b,
        unsigned int a)
{
  *(_BYTE *)pValue = b;
  *((_BYTE *)pValue + 1) = g;
  *((_BYTE *)pValue + 2) = r;
  *((_BYTE *)pValue + 3) = a;
  return pValue;
}

// source: b/4/tga.c:90  [anchor-strings]
int __cdecl TGA_ReadPaletteEntry(struct File_s *ptFile, unsigned int *Value, int Size)
{
  unsigned __int8 v3; // bl
  unsigned __int8 v4; // al
  unsigned __int8 v5; // cl
  unsigned __int8 v6; // dl
  unsigned __int8 v7; // al
  unsigned __int8 v8; // cl
  int v9; // edx
  unsigned __int8 v11; // [esp+Ah] [ebp-2h]

  switch ( Size )
  {
    case 8:
      v3 = TGA_pnFile[TGA_nFilePos++];
      v4 = v3;
      v5 = v3;
      v11 = -1;
      break;
    case 15:
    case 16:
      v6 = TGA_pnFile[TGA_nFilePos];
      v7 = TGA_pnFile[TGA_nFilePos + 1];
      TGA_nFilePos += 2;
      v8 = v7;
      v4 = ((v6 >> 2) & 0x38) + ((v7 & 3) << 6);
      v5 = 2 * (v8 & 0xFC);
      v3 = 8 * v6;
      v11 = -1;
      break;
    case 24:
    case 32:
      v3 = TGA_pnFile[TGA_nFilePos];
      v4 = TGA_pnFile[TGA_nFilePos + 1];
      v5 = TGA_pnFile[TGA_nFilePos + 2];
      v9 = TGA_nFilePos + 3;
      TGA_nFilePos += 3;
      if ( Size == 32 )
      {
        v11 = TGA_pnFile[v9];
        TGA_nFilePos = v9 + 1;
      }
      else
      {
        v11 = -1;
      }
      break;
    default:
      LDebug_Error("Unknown colormap pixel size (#2) - %d", Size);
      abort();
  }
  *((_BYTE *)Value + 2) = v5;
  *(_BYTE *)Value = v3;
  *((_BYTE *)Value + 1) = v4;
  *((_BYTE *)Value + 3) = v11;
  return 1;
}

// source: b/4/tga.c:157  [anchor-strings]
int __cdecl TGA_ReadPixel(struct File_s *ptFile, unsigned int *dest, int Size)
{
  unsigned __int8 v3; // dl
  int v4; // eax
  int v5; // ecx
  unsigned __int8 v6; // cl
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  unsigned __int8 v10; // cl
  unsigned int v11; // esi
  unsigned __int8 v12; // cl
  int v13; // eax
  int v14; // eax
  unsigned __int8 v15; // cl
  char v17; // cl

  if ( !TGA_isRLEEncoded )
  {
LABEL_8:
    v4 = TGA_nFilePos;
    goto LABEL_9;
  }
  if ( TGA_nRLECount )
  {
    --TGA_nRLECount;
    if ( TGA_bRLEFlag )
    {
      LOBYTE(v9) = dword_7EEEB48;
      LOBYTE(v8) = dword_7EFEB5C;
      v7 = dword_834DB0C;
      goto LABEL_17;
    }
    goto LABEL_8;
  }
  v3 = TGA_pnFile[TGA_nFilePos];
  v4 = ++TGA_nFilePos;
  TGA_bRLEFlag = v3 & 0x80;
  if ( (v3 & 0x80) != 0 )
    v5 = v3 - 127;
  else
    v5 = v3 + 1;
  TGA_nRLECount = v5 - 1;
LABEL_9:
  switch ( Size )
  {
    case 8:
      v6 = TGA_pnFile[v4];
      TGA_nFilePos = v4 + 1;
      v7 = v6;
      LOBYTE(v8) = v6;
      LOBYTE(v9) = v6;
      dword_834DB0C = v6;
      dword_7EFEB54 = v6;
      dword_7EFEB5C = v6;
      dword_7EEEB48 = v6;
      dword_7EFEB50 = 255;
      break;
    case 15:
    case 16:
      v10 = TGA_pnFile[v4 + 1];
      v11 = TGA_pnFile[v4];
      TGA_nFilePos = v4 + 2;
      v7 = v11 + (v10 << 8);
      LOBYTE(v9) = 2 * (v10 & 0x7C);
      v8 = ((v10 & 3) << 6) + ((v11 >> 2) & 0x3FFFFFF8);
      dword_834DB0C = v7;
      dword_7EEEB48 = 2 * (v10 & 0x7C);
      dword_7EFEB5C = v8;
      dword_7EFEB54 = 8 * (v11 & 0x1F);
      dword_7EFEB50 = 255;
      break;
    case 24:
    case 32:
      v8 = TGA_pnFile[v4];
      v12 = TGA_pnFile[v4 + 1];
      v13 = v4 + 2;
      dword_7EFEB54 = v8;
      LOBYTE(v8) = v12;
      v9 = TGA_pnFile[v13];
      v14 = v13 + 1;
      dword_7EFEB5C = v12;
      TGA_nFilePos = v14;
      dword_7EEEB48 = v9;
      if ( Size == 32 )
      {
        v15 = TGA_pnFile[v14];
        TGA_nFilePos = v14 + 1;
        dword_7EFEB50 = v15;
        v7 = 0;
      }
      else
      {
        v7 = 0;
        dword_7EFEB50 = 255;
      }
      dword_834DB0C = 0;
      break;
    default:
      LDebug_Error("TGA_Load(): Unknown pixel size (#2) - %d", Size);
      abort();
  }
LABEL_17:
  if ( TGA_isMapped )
  {
    *dest = TGA_anColorMap[v7];
  }
  else
  {
    v17 = dword_7EFEB50;
    *(_BYTE *)dest = dword_7EFEB54;
    *((_BYTE *)dest + 2) = v9;
    *((_BYTE *)dest + 1) = v8;
    *((_BYTE *)dest + 3) = v17;
  }
  return 1;
}

// source: b/4/tga.c:260  [anchor-callee]
void __cdecl TGA_ReadHeader(struct File_s *ptFile, struct TGAHeader_s *ptTGAHeader)
{
  int v2; // eax
  unsigned __int8 *v3; // esi
  unsigned __int8 v4; // dl
  unsigned __int8 v5; // dl
  unsigned __int8 v6; // dl
  unsigned __int8 v7; // dl
  unsigned __int8 v8; // dl
  unsigned __int8 v9; // dl
  unsigned __int8 v10; // dl
  unsigned __int8 v11; // dl
  unsigned __int8 v12; // dl
  unsigned __int8 v13; // dl
  unsigned __int8 v14; // dl
  unsigned __int8 v15; // dl
  unsigned __int8 v16; // dl
  unsigned __int8 v17; // dl
  unsigned __int8 v18; // dl
  int v19; // eax
  unsigned __int8 v20; // [esp+Bh] [ebp-1h]

  v2 = TGA_nFilePos + 3;
  v3 = TGA_pnFile;
  v20 = TGA_pnFile[TGA_nFilePos];
  ptTGAHeader->IDLength = v20;
  ptTGAHeader->CoMapType = v3[v2 - 2];
  ptTGAHeader->ImgType = v3[v2 - 1];
  v4 = v3[v2++];
  ptTGAHeader->Index_lo = v4;
  v5 = v3[v2++];
  ptTGAHeader->Index_hi = v5;
  v6 = v3[v2++];
  ptTGAHeader->Length_lo = v6;
  v7 = v3[v2++];
  ptTGAHeader->Length_hi = v7;
  v8 = v3[v2++];
  ptTGAHeader->CoSize = v8;
  v9 = v3[v2++];
  ptTGAHeader->X_org_lo = v9;
  v10 = v3[v2++];
  ptTGAHeader->X_org_hi = v10;
  v11 = v3[v2++];
  ptTGAHeader->Y_org_lo = v11;
  v12 = v3[v2++];
  ptTGAHeader->Y_org_hi = v12;
  v13 = v3[v2++];
  ptTGAHeader->Width_lo = v13;
  v14 = v3[v2++];
  ptTGAHeader->Width_hi = v14;
  v15 = v3[v2++];
  ptTGAHeader->Height_lo = v15;
  v16 = v3[v2++];
  ptTGAHeader->Height_hi = v16;
  v17 = v3[v2++];
  ptTGAHeader->PixelSize = v17;
  v18 = v3[v2];
  ptTGAHeader->AttBits = v18 & 0xF;
  ptTGAHeader->Rsrvd = (v18 & 0x10) != 0;
  ptTGAHeader->IntrLve = v18 >> 6;
  v19 = v2 + 1;
  ptTGAHeader->OrgBit = (v18 & 0x20) != 0;
  TGA_nFilePos = v19;
  if ( v20 )
    TGA_nFilePos = ptTGAHeader->IDLength + v19;
}

// source: b/4/tga.c:312  [anchor-strings]
int __cdecl TGA_Read(unsigned int **ppbData, int *pnWidth, int *pnHeight, char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v25; };
    struct { char igi2_o1[4]; int v26; };
    struct { char igi2_o2[8]; int v27; };
    struct { char igi2_o3[12]; int v28; };
    struct { char igi2_o4[16]; int v29; };
    struct { char igi2_o5[16]; int v30; };
    struct { char igi2_o6[20]; unsigned __int8 *pxData; };
    struct { char igi2_o7[24]; int v32; };
    struct { char igi2_o8[28]; int v33; };
    struct { char igi2_o9[32]; int v34; };
    struct { char igi2_o10[36]; int v35; };
    struct { char igi2_o11[40]; struct Resource_s *pptResource; };
    struct { char igi2_o12[44]; int v37; };
    struct { char igi2_o13[48]; int v38; };
    struct { char igi2_o14[52]; int v39; };
    struct { char igi2_o15[56]; int v40; };
    struct { char igi2_o16[60]; struct TGAHeader_s ptTGAHeader; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v5; // ecx
  struct Resource_s *v6; // eax
  unsigned __int8 *v7; // eax
  void *v8; // eax
  int v9; // ebp
  unsigned __int8 ImgType; // dl
  int v11; // esi
  unsigned int v12; // eax
  struct Resource_s *v13; // ecx
  unsigned int *v14; // ebx
  int v15; // eax
  int v16; // edx
  int v17; // ebx
  int v18; // edi
  int v19; // ebp
  int PixelSize; // edi
  unsigned int *v21; // ebp
  int v22; // ebp
  int v23; // ecx

  if ( Resource_IsLoadedInternal(zFilename, &igi2_frame.pptResource) )
  {
    v6 = igi2_frame.pptResource;
    igi2_frame.pptResource->isReferenced = 1;
    v7 = (unsigned __int8 *)v6->pxData;
    igi2_frame.pxData = v7;
  }
  else
  {
    Game_MPRunNetwork(v5);
    v8 = File_Load(zFilename, (unsigned int *)&igi2_frame.pptResource);
    if ( !v8 )
    {
      LDebug_Error("Failed to load resource: '%s'", zFilename);
      goto LABEL_5;
    }
    v7 = (unsigned __int8 *)Resource_ParseFile(File_zLastSubstitutedPath, v8, (unsigned int)igi2_frame.pptResource);
    igi2_frame.pxData = v7;
  }
  if ( !v7 )
  {
    LDebug_Error("Failed to read file \"%s\"", zFilename);
    goto LABEL_5;
  }
  TGA_pnFile = v7;
  TGA_nFilePos = 0;
  TGA_nRLECount = 0;
  TGA_bRLEFlag = 0;
  TGA_ReadHeader(nullptr, &igi2_frame.ptTGAHeader);
  v9 = igi2_frame.ptTGAHeader.Height_lo + (igi2_frame.ptTGAHeader.Height_hi << 8);
  ImgType = igi2_frame.ptTGAHeader.ImgType;
  v11 = igi2_frame.ptTGAHeader.Width_lo + (igi2_frame.ptTGAHeader.Width_hi << 8);
  igi2_frame.v35 = v9;
  switch ( igi2_frame.ptTGAHeader.ImgType )
  {
    case 1u:
    case 2u:
    case 3u:
    case 9u:
    case 0xAu:
    case 0xBu:
      if ( igi2_frame.ptTGAHeader.ImgType == 1
        || igi2_frame.ptTGAHeader.ImgType == 9
        || igi2_frame.ptTGAHeader.ImgType == 32
        || igi2_frame.ptTGAHeader.ImgType == 33 )
      {
        if ( igi2_frame.ptTGAHeader.CoMapType != 1 )
        {
          LDebug_Error("TGA_Load(): Mapped image (type %d) with color map type != 1", igi2_frame.ptTGAHeader.ImgType);
LABEL_5:
          abort();
        }
        TGA_isMapped = 1;
      }
      else
      {
        TGA_isMapped = 0;
        if ( !igi2_frame.ptTGAHeader.CoMapType )
        {
LABEL_25:
          if ( ImgType == 9 || ImgType == 10 || (TGA_isRLEEncoded = 0, ImgType == 11) )
            TGA_isRLEEncoded = 1;
          igi2_frame.v37 = 4 * v9 * v11;
          igi2_frame.pptResource = (struct Resource_s *)Mem_AllocFn(igi2_frame.v37, 4);
          igi2_frame.v25 = 0;
          igi2_frame.v28 = 0;
          if ( v9 > 0 )
          {
            v15 = 16 * v11;
            v16 = -8 * v11;
            v17 = -4 * v11;
            v18 = -16 * v11;
            igi2_frame.v26 = 0;
            igi2_frame.v27 = 0;
            igi2_frame.v33 = 0;
            igi2_frame.v38 = 16 * v11;
            igi2_frame.v30 = 0;
            igi2_frame.v39 = -8 * v11;
            igi2_frame.v40 = -16 * v11;
            igi2_frame.v34 = v9;
            do
            {
              v19 = igi2_frame.v26;
              if ( !igi2_frame.ptTGAHeader.OrgBit )
                v19 = v17 + igi2_frame.v27 + igi2_frame.v37;
              if ( v11 > 0 )
              {
                PixelSize = igi2_frame.ptTGAHeader.PixelSize;
                v21 = (unsigned int *)((char *)igi2_frame.pptResource + v19);
                igi2_frame.v32 = v11;
                do
                {
                  TGA_ReadPixel(nullptr, v21++, PixelSize);
                  --igi2_frame.v32;
                }
                while ( igi2_frame.v32 );
                v15 = igi2_frame.v38;
                v16 = igi2_frame.v39;
                v18 = igi2_frame.v40;
              }
              if ( igi2_frame.ptTGAHeader.IntrLve == 2 )
              {
                igi2_frame.v25 += 4;
                v22 = v15 + igi2_frame.v26;
                v23 = v18 + igi2_frame.v27;
              }
              else if ( igi2_frame.ptTGAHeader.IntrLve == 1 )
              {
                igi2_frame.v25 += 2;
                v22 = 8 * v11 + igi2_frame.v26;
                v23 = v16 + igi2_frame.v27;
              }
              else
              {
                ++igi2_frame.v25;
                v22 = 4 * v11 + igi2_frame.v26;
                v23 = v17 + igi2_frame.v27;
              }
              igi2_frame.v26 = v22;
              igi2_frame.v27 = v23;
              if ( igi2_frame.v25 >= igi2_frame.v35 )
              {
                ++igi2_frame.v28;
                igi2_frame.v30 += v17;
                igi2_frame.v25 = igi2_frame.v28;
                igi2_frame.v33 += 4 * v11;
                igi2_frame.v26 = igi2_frame.v33;
                igi2_frame.v27 = igi2_frame.v30;
              }
              --igi2_frame.v34;
            }
            while ( igi2_frame.v34 );
            v9 = igi2_frame.v35;
          }
          *ppbData = (unsigned int *)igi2_frame.pptResource;
          *pnWidth = v11;
          *pnHeight = v9;
          TGA_pnFile = nullptr;
          Resource_Flush(igi2_frame.pxData);
          return 1;
        }
      }
      v12 = igi2_frame.ptTGAHeader.Index_lo + (igi2_frame.ptTGAHeader.Index_hi << 8);
      v13 = (struct Resource_s *)(v12 + igi2_frame.ptTGAHeader.Length_lo + (igi2_frame.ptTGAHeader.Length_hi << 8));
      igi2_frame.pptResource = v13;
      if ( (unsigned int)&v13->ptNext + 1 >= 0x4000 )
      {
        LDebug_Error("TGA_Load(): Too many colors - %d", (char *)&v13->ptNext + 1);
        goto LABEL_5;
      }
      igi2_frame.v29 = igi2_frame.ptTGAHeader.Index_lo + (igi2_frame.ptTGAHeader.Index_hi << 8);
      if ( v12 >= (unsigned int)v13 )
        goto LABEL_25;
      v14 = (unsigned int *)(4 * v12 + 133098320);
      while ( TGA_ReadPaletteEntry(nullptr, v14, igi2_frame.ptTGAHeader.CoSize) )
      {
        ++v14;
        if ( ++igi2_frame.v29 >= (unsigned int)igi2_frame.pptResource )
        {
          ImgType = igi2_frame.ptTGAHeader.ImgType;
          goto LABEL_25;
        }
      }
      return 0;
    default:
      LDebug_Error("TGA_Load(): Unknown Targa image type %d", igi2_frame.ptTGAHeader.ImgType);
      goto LABEL_5;
  }
}

// source: b/4/tga.c:499  [anchor-strings]
int __cdecl TGA_Write(char *zFilename, unsigned int *pbData, int nWidth, int nHeight)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int *v13; };
    struct { char igi2_o1[4]; int v14; };
    struct { char igi2_o2[12]; struct TGAHeader_s tTGAHeader; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct File_s *v5; // eax
  struct File_s *v6; // esi
  int v7; // ecx
  unsigned int *v8; // edi
  int v9; // ebp
  bool v10; // zf
  char *RealFilename; // eax

  v5 = File_New(zFilename, "w");
  v6 = v5;
  if ( !v5 )
  {
    RealFilename = File_GetRealFilename(zFilename);
    LDebug_Error("TGA_Write(): Failed to open file '%s' for writing.", RealFilename);
    abort();
  }
  *(_DWORD *)&igi2_frame.tTGAHeader.IDLength = 0x20000;
  *(_DWORD *)&igi2_frame.tTGAHeader.Index_hi = 0;
  *(_DWORD *)&igi2_frame.tTGAHeader.X_org_lo = 0;
  igi2_frame.tTGAHeader.OrgBit = 0;
  igi2_frame.tTGAHeader.IntrLve = 0;
  igi2_frame.tTGAHeader.Width_hi = nWidth / 256;
  igi2_frame.tTGAHeader.Height_lo = nHeight;
  igi2_frame.tTGAHeader.Width_lo = nWidth;
  *(_DWORD *)&igi2_frame.tTGAHeader.Height_hi = (unsigned __int8)(nHeight / 256);
  igi2_frame.tTGAHeader.PixelSize = 32;
  File_atDevice[v5->eDeviceID].pfWrite(v5->eDeviceID, v5, &igi2_frame.tTGAHeader, 18u);
  if ( nHeight - 1 >= 0 )
  {
    v7 = -1 * nWidth;
    v8 = &pbData[nWidth * (nHeight - 1)];
    igi2_frame.v13 = v8;
    igi2_frame.v14 = nHeight;
    do
    {
      if ( nWidth > 0 )
      {
        v9 = nWidth;
        do
        {
          File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, v8++, 4u);
          --v9;
        }
        while ( v9 );
        v7 = -1 * nWidth;
      }
      v8 = &igi2_frame.v13[v7];
      v10 = igi2_frame.v14 == 1;
      igi2_frame.v13 = (unsigned int *)((char *)igi2_frame.v13 + v7 * 4);
      --igi2_frame.v14;
    }
    while ( !v10 );
  }
  if ( v6 == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[v6->eDeviceID].pfDelete(v6->eDeviceID, v6);
  return 0;
}

// source: b/4/tga.c:555  [size]
void __cdecl TGA_Open()
{
  ;
}

// source: b/4/tga.c:567  [size]
void __cdecl TGA_Close()
{
  ;
}
