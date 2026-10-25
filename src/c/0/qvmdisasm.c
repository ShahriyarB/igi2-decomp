/* c/0/qvmdisasm.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/qvmdisasm.c:37  [anchor-strings]
int __cdecl QVMDisAsm_Disassemble(
        char *zDestinationFile,
        struct QVM_s *ptQVM,
        int nStartPC,
        int nEndPC)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iOpCode; };
    struct { char igi2_o1[4]; char *v21; };
    struct { char igi2_o2[8]; void (__cdecl **v22)(void *, void *, int, int); };
    struct { char igi2_o3[12]; struct QVMGetNameContext_s tGetNameContext; };
    struct { char igi2_o4[20]; struct QVMDisAsmContext_s tDisAsmContext; };
    struct { char igi2_o5[32]; struct File_s *ptFile; };
    struct { char igi2_o6[36]; char zAddress[256]; };
    struct { char igi2_o7[292]; _BYTE azOpCodeName[492]; };
    char igi2_extent[784];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nProgamSize; // edi
  struct File_s *v5; // ebx
  void (__cdecl **v6)(void *, void *, int, int); // esi
  int v7; // ebp
  struct QVMGetNameContext_s *p_tGetNameContext; // eax
  char v9; // cl
  int v10; // edx
  struct QVM_s *v11; // esi
  int nPC; // ecx
  int v13; // kr00_4
  int v14; // edx
  int eDeviceID; // eax
  unsigned __int8 v16; // cl
  unsigned int v17; // eax
  void (__cdecl *v18)(void *, void *, int, int); // edx

  nProgamSize = nStartPC;
  v5 = File_New(zDestinationFile, "w");
  igi2_frame.ptFile = v5;
  if ( v5 )
  {
    v6 = &QVM_atOpCode[0].apfOpCodeEvent[1];
    igi2_frame.iOpCode = 0;
    igi2_frame.v21 = igi2_frame.azOpCodeName;
    igi2_frame.v22 = &QVM_atOpCode[0].apfOpCodeEvent[1];
    v7 = -(int)&igi2_frame.tGetNameContext;
    do
    {
      if ( (int)v6 >= 139287148 && (int)v6 < 139288324 && *v6 )
        (*v6)(&igi2_frame.tGetNameContext, nullptr, igi2_frame.iOpCode, 1);
      p_tGetNameContext = &igi2_frame.tGetNameContext;
      do
      {
        v9 = p_tGetNameContext->zName[0];
        igi2_frame.azOpCodeName[v7 + (_DWORD)p_tGetNameContext] = p_tGetNameContext->zName[0];
        p_tGetNameContext = (struct QVMGetNameContext_s *)((char *)p_tGetNameContext + 1);
      }
      while ( v9 );
      v10 = strlen(igi2_frame.v21);
      if ( v10 <= 8 )
      {
        memset(&igi2_frame.tGetNameContext.zName[(_DWORD)&igi2_frame.azOpCodeName[v10 + v7]], 0x20u, 9 - v10);
        v5 = igi2_frame.ptFile;
        nProgamSize = nStartPC;
        v10 = 9;
        v6 = igi2_frame.v22;
      }
      igi2_frame.tGetNameContext.zName[(_DWORD)&igi2_frame.azOpCodeName[v10 + v7]] = 0;
      v6 += 6;
      v7 += 10;
      ++igi2_frame.iOpCode;
      igi2_frame.v22 = v6;
      igi2_frame.v21 += 10;
    }
    while ( (int)v6 < 139288324 );
    v11 = ptQVM;
    if ( nProgamSize >= 0 )
    {
      if ( ptQVM->nProgamSize < nProgamSize )
        nProgamSize = ptQVM->nProgamSize;
    }
    else
    {
      nProgamSize = 0;
    }
    if ( nEndPC >= 0 )
    {
      if ( ptQVM->nProgamSize < nEndPC )
        nEndPC = ptQVM->nProgamSize;
    }
    else
    {
      nEndPC = 0;
    }
    nPC = nProgamSize;
    igi2_frame.tDisAsmContext.ptFile = v5;
    igi2_frame.tDisAsmContext.nPC = nProgamSize;
    igi2_frame.tDisAsmContext.nTab = 20;
    while ( 1 )
    {
      sprintf(igi2_frame.zAddress, "%08X:", nPC);
      v13 = strlen(igi2_frame.zAddress);
      v14 = v13;
      if ( v13 < 11 )
      {
        memset(&igi2_frame.zAddress[v13], 0x20u, 11 - v13);
        v14 = 11;
        v11 = ptQVM;
      }
      eDeviceID = v5->eDeviceID;
      igi2_frame.zAddress[v14] = 0;
      File_atDevice[eDeviceID].pfWrite(eDeviceID, v5, igi2_frame.zAddress, 11u);
      v16 = v11->anInstruction[igi2_frame.tDisAsmContext.nPC];
      if ( v16 >= 0x31u )
        break;
      File_atDevice[v5->eDeviceID].pfWrite(v5->eDeviceID, v5, &igi2_frame.azOpCodeName[10 * v16], 8u);
      nPC = igi2_frame.tDisAsmContext.nPC;
      v17 = v11->anInstruction[igi2_frame.tDisAsmContext.nPC];
      if ( v17 < 0x31 )
      {
        v18 = QVM_atOpCode[v17].apfOpCodeEvent[3];
        if ( v18 )
        {
          v18(&igi2_frame.tDisAsmContext, v11, v17, 3);
          nPC = igi2_frame.tDisAsmContext.nPC;
        }
      }
      if ( nPC >= nEndPC )
        goto LABEL_30;
    }
    sprintf(igi2_frame.zAddress, "ILLEGAL\r\n");
    File_atDevice[v5->eDeviceID].pfWrite(v5->eDeviceID, v5, igi2_frame.zAddress, strlen(igi2_frame.zAddress));
LABEL_30:
    if ( v5 == &File_tDummyAsyncFile )
    {
      File_tDummyAsyncFile.isAsync = false;
      return 0;
    }
    File_atDevice[v5->eDeviceID].pfDelete(v5->eDeviceID, v5);
  }
  return 0;
}

// source: c/0/qvmdisasm.c:115  [size]
// attributes: thunk
void __cdecl QVMDisAsm_Open()
{
  QVMOpCode_LinkDisAsmHandlers();
}

// source: c/0/qvmdisasm.c:128  [size]
void __cdecl QVMDisAsm_Close()
{
  ;
}
