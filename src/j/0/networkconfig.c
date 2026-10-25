/* j/0/networkconfig.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/networkconfig.c:87  [anchor-strings]
void __cdecl NetworkConfig_DefaultOptions()
{
  strcpy(ClientConfig_tClientConfig.zPlayerName, "Jones");
  ClientConfig_tClientConfig.zPlayerPassword[0] = 0;
  strcpy(ServerConfig_tServerConfig.zServerName, "IGI2 Server");
  strncpy(
    ServerConfig_tServerConfig.zRConPassword,
    (char *)&g_zFileName.atSpriteResources[40].tSprite.atQAnimframe,
    0x40u);
  ServerConfig_tServerConfig.nMoneyCap = 1000;
  ServerConfig_tServerConfig.nMoneyObjectiveTeamWin = 1000;
  ServerConfig_tServerConfig.nSpawnTimeToFree = 1000;
  ServerConfig_tServerConfig.nMoneyMissionWin = 1250;
  ServerConfig_tServerConfig.nMoneyMissionLost = 1250;
  ServerConfig_tServerConfig.nCloseFireRange = 100;
  ServerConfig_tServerConfig.nSmoothPercent = 100;
  ServerConfig_tServerConfig.isTeamDamage = 100;
  ServerConfig_tServerConfig.zServerPassword[0] = 0;
  ServerConfig_tServerConfig.nClientPort = 0;
  ServerConfig_tServerConfig.isPublic = false;
  ServerConfig_tServerConfig.nWarmup = 0;
  ServerConfig_tServerConfig.nPloss = 0;
  ServerConfig_tServerConfig.nMapMaxTime = 0;
  ServerConfig_tServerConfig.nMapMaxTeamScore = 0;
  ServerConfig_tServerConfig.isLocalWeapon = false;
  ServerConfig_tServerConfig.nBombReposTime = 0;
  ServerConfig_tServerConfig.isForceFirstSpec = false;
  ServerConfig_tServerConfig.nPort = 26001;
  ServerConfig_tServerConfig.nMaxPlayers = 26015;
  ServerConfig_tServerConfig.isAutoBalance = true;
  ServerConfig_tServerConfig.nSpectateMode = 16;
  ServerConfig_tServerConfig.nMoneyStart = 1;
  ServerConfig_tServerConfig.nMoneyKill = 15000;
  ServerConfig_tServerConfig.nMoneyTeamKill = 800;
  ServerConfig_tServerConfig.nMoneyObjectivePlayerWin = -4000;
  ServerConfig_tServerConfig.nMoneyObjectiveTeamLost = 2250;
  ServerConfig_tServerConfig.nMapMaxRounds = 750;
  ServerConfig_tServerConfig.nObjectiveMaxTime = 3;
  ServerConfig_tServerConfig.nBombTime = 15;
  ServerConfig_tServerConfig.nSpawnMaxCost = 90;
  ServerConfig_tServerConfig.nSpawnSafeTime = 20;
  ServerConfig_tServerConfig.nTimeOut = 10;
  ServerConfig_tServerConfig.nAutoKick = 90;
  LODWORD(ServerConfig_tServerConfig.vSendDiffSpeed) = 300;
  ServerConfig_tServerConfig.nViewPosRange = 20;
  ServerConfig_tServerConfig.nViewFireRange = 20;
  ClientConfig_tClientConfig.nBandwidth = 400;
  pValue_84b73b4 = (struct Result_s *)60;
  pValue_84b73b8 = (struct Result_s *)12;
  ServerConfig_tServerConfig.isAllowSniperRifles = true;
  ServerConfig_tServerConfig.nPlossMax = 150;
  ServerConfig_tServerConfig.nPingMax = 400;
  ServerConfig_tServerConfig.nGoutMax = 45;
  ServerConfig_tServerConfig.nIdleMax = 3000;
}

// source: j/0/networkconfig.c:187  [size~]
char *__cdecl NetworkConfig_Load(char *zNetworkConfigFileName)
{
  FILE *v1; // esi
  char *result; // eax
  char Buffer[1024]; // [esp+4h] [ebp-400h] BYREF

  v1 = fopen(zNetworkConfigFileName, "r");
  NetworkConfig_DefaultOptions();
  if ( v1 )
  {
    while ( !feof(v1) )
    {
      if ( fgets(Buffer, 1024, v1) && Buffer[0] != 47 && Buffer[0] != 10 )
        NetworkCommand_ParseEvalCommandLine(Buffer);
    }
    return (char *)fclose(v1);
  }
  return result;
}

// source: j/0/networkconfig.c:216  [anchor-strings]
void __cdecl NetworkConfig_WriteString(struct File_s *ptFile, char *zProperty)
{
  #pragma pack(push, 1)
  union
  {
    struct { double v; };
    struct { char igi2_o1[8]; char zValue[64]; };
    struct { char igi2_o2[72]; char zEval[64]; };
    struct { char igi2_o3[136]; char zBuffer[256]; };
    char igi2_extent[392];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char v2; // cl
  unsigned int v3; // eax

  memset(igi2_frame.zValue, 0, sizeof(igi2_frame.zValue));
  _snprintf(igi2_frame.zEval, 0x40u, (char *const)&g_zFileName.atSpriteResources[40].tSprite, zProperty);
  ScriptDebugger_EvaluateExpression(igi2_frame.zEval, &igi2_frame.v);
  LODWORD(igi2_frame.v) = strlen(NetworkCommand_zEvalResponse);
  if ( LODWORD(igi2_frame.v) )
  {
    strncat(igi2_frame.zValue, NetworkCommand_zEvalResponse, 0x40u);
    igi2_frame.zValue[63] = 0;
  }
  else
  {
    igi2_frame.zValue[0] = v2;
  }
  v3 = _snprintf(igi2_frame.zBuffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[48], zProperty, igi2_frame.zValue);
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.zBuffer, v3);
}

// source: j/0/networkconfig.c:282  [anchor-refs]
void __cdecl NetworkConfig_WriteInt(struct File_s *ptFile, char *zProperty)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 v; };
    struct { char igi2_o1[8]; char zEval[64]; };
    struct { char igi2_o2[72]; char zBuffer[260]; };
    char igi2_extent[332];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v2; // eax

  _snprintf(igi2_frame.zEval, 0x40u, (char *const)&g_zFileName.atSpriteResources[40].tSprite);
  ScriptDebugger_EvaluateExpression(igi2_frame.zEval, (double *)&igi2_frame.v);
  igi2_frame.v = (__int64)*(double *)&igi2_frame.v;
  v2 = sprintf(igi2_frame.zBuffer, "lo %s %d\r\n", zProperty, (_DWORD)igi2_frame.v);
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.zBuffer, v2);
}

// source: j/0/networkconfig.c:304  [anchor-callee]
void __cdecl NetworkConfig_Save(char *zNetworkConfigFileName)
{
  struct File_s *v2; // edi
  unsigned int v3; // eax
  unsigned int v4; // eax
  unsigned int v5; // eax
  unsigned int v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  unsigned int v9; // eax
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  unsigned int v13; // eax
  unsigned int v14; // eax
  unsigned int v15; // eax
  unsigned int v16; // eax
  unsigned int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // eax
  unsigned int v20; // eax
  unsigned int v21; // eax
  unsigned int v22; // eax
  unsigned int v23; // eax
  unsigned int v24; // eax
  unsigned int v25; // eax
  unsigned int v26; // eax
  unsigned int v27; // eax
  unsigned int v28; // eax
  unsigned int v29; // eax
  unsigned int v30; // eax
  unsigned int v31; // eax
  unsigned int v32; // eax
  unsigned int v33; // eax
  unsigned int v34; // eax
  unsigned int v35; // eax
  unsigned int v36; // eax
  unsigned int v37; // eax
  unsigned int v38; // eax
  unsigned int v39; // eax
  unsigned int v40; // eax
  unsigned int v41; // eax
  unsigned int v42; // eax
  unsigned int v43; // eax
  unsigned int v44; // eax
  unsigned int v45; // eax
  unsigned int v46; // eax
  unsigned int v47; // eax
  unsigned int v48; // eax
  char Buffer[260]; // [esp+10h] [ebp-104h] BYREF

  v2 = File_New(zNetworkConfigFileName, "w");
  if ( !v2 )
  {
    LDebug_Error(&g_zFileName.atSpriteResources[40].zResourceFilename[4], zNetworkConfigFileName);
    abort();
  }
  v3 = _snprintf(
         Buffer,
         0x100u,
         &g_zFileName.atSpriteResources[40].zResourceFilename[40],
         &g_zFileName.atSpriteResources[39].tSprite);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v3);
  v4 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v4);
  v5 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v5);
  v6 = _snprintf(
         Buffer,
         0x100u,
         &g_zFileName.atSpriteResources[40].zResourceFilename[40],
         &g_zFileName.atSpriteResources[39].zResourceFilename[20]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v6);
  v7 = _snprintf(
         Buffer,
         0x100u,
         &g_zFileName.atSpriteResources[40].zResourceFilename[40],
         &g_zFileName.atSpriteResources[38].zResourceFilename[16]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v7);
  v8 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v8);
  v9 = _snprintf(
         Buffer,
         0x100u,
         &g_zFileName.atSpriteResources[40].zResourceFilename[40],
         &g_zFileName.atSpriteResources[37].zResourceFilename[40]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v9);
  v10 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[36].tSprite.atTexInfo);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v10);
  v11 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v11);
  v12 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[35].tSprite);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v12);
  v13 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[35].zResourceFilename[28]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v13);
  NetworkConfig_WriteString(v2, &g_zFileName.atSpriteResources[35].zResourceFilename[20]);
  v14 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v14);
  v15 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[34].zResourceFilename[32]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v15);
  NetworkConfig_WriteString(v2, &g_zFileName.atSpriteResources[34].zResourceFilename[20]);
  v16 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v16);
  v17 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[33].zResourceFilename[44]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v17);
  NetworkConfig_WriteString(v2, &g_zFileName.atSpriteResources[33].zResourceFilename[32]);
  v18 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v18);
  v19 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[32].tSprite.atQAnimframe);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v19);
  v20 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[32].zResourceFilename[28]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v20);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[32].zResourceFilename[20]);
  v21 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v21);
  v22 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[31].zResourceFilename[24]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v22);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[31].zResourceFilename[12]);
  v23 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v23);
  v24 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[30].zResourceFilename[16]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v24);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[30].zResourceFilename[8]);
  v25 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v25);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[29].tSprite.nQAnimframes);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[29].tSprite.atQAnimframe);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[29].zResourceFilename[60]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[29].zResourceFilename[48]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[29].zResourceFilename[40]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[29].zResourceFilename[32]);
  v26 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v26);
  v27 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[28].tSprite);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v27);
  v28 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[28].zResourceFilename[8]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v28);
  v29 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[27].zResourceFilename[40]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v29);
  v30 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[27].zResourceFilename[12]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v30);
  v31 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v31);
  v32 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[26].tSprite.nQAnimframes);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v32);
  v33 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[26].tSprite);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v33);
  v34 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[26].zResourceFilename[48]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v34);
  v35 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[26].zResourceFilename[28]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v35);
  v36 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[26].zResourceFilename[4]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v36);
  v37 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v37);
  NetManager_WriteActiveMaps(v2, (char *)&stru_6A1E00.nLastRun);
  v38 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v38);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[25].tSprite.nTextures);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[25].tSprite.atTexInfo);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[25].zResourceFilename[56]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[25].zResourceFilename[40]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[25].zResourceFilename[20]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[25].zResourceFilename[4]);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[24].tSprite.atQAnimframe);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[24].zResourceFilename[56]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[24].zResourceFilename[36]);
  v39 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v39);
  v40 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[23].tSprite.atTexInfo);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v40);
  v41 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[23].zResourceFilename[28]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v41);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[23].zResourceFilename[16]);
  v42 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v42);
  v43 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[22].tSprite);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v43);
  v44 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[22].zResourceFilename[32]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v44);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[22].zResourceFilename[24]);
  v45 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v45);
  v46 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[21].tSprite);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v46);
  v47 = _snprintf(
          Buffer,
          0x100u,
          &g_zFileName.atSpriteResources[40].zResourceFilename[40],
          &g_zFileName.atSpriteResources[21].zResourceFilename[24]);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v47);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[21].zResourceFilename[8]);
  v48 = _snprintf(Buffer, 0x100u, &g_zFileName.atSpriteResources[40].zResourceFilename[40], &g_zInitialValue);
  File_atDevice[v2->eDeviceID].pfWrite(v2->eDeviceID, v2, Buffer, v48);
  NetworkConfig_WriteInt(v2, g_zFileName.atSpriteResources[21].zResourceFilename);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[20].tSprite.ptQTilemap);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[20].tSprite);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[20].zResourceFilename[52]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[20].zResourceFilename[36]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[20].zResourceFilename[16]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[20].zResourceFilename[8]);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[19].tSprite.nQAnimframes);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[19].tSprite.ptQTilemap);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[19].tSprite);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[19].zResourceFilename[56]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[19].zResourceFilename[44]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[19].zResourceFilename[36]);
  NetworkConfig_WriteString(v2, &g_zFileName.atSpriteResources[19].zResourceFilename[24]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[19].zResourceFilename[8]);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[18].tSprite.nTextures);
  NetworkConfig_WriteInt(v2, (char *)&g_zFileName.atSpriteResources[18].tSprite.atQAnimframe);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[18].zResourceFilename[60]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[18].zResourceFilename[52]);
  NetworkConfig_WriteInt(v2, &g_zFileName.atSpriteResources[18].zResourceFilename[44]);
  if ( v2 == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[v2->eDeviceID].pfDelete(v2->eDeviceID, v2);
}

// source: j/0/networkconfig.c:395  [anchor-mhash]
struct Result_s *__cdecl NetworkConfig_FillInputBoxInt(
        struct Result_s *retstr,
        int nValue,
        int ltcg_ebx)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[64]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // eax
  int v4; // edx
  char v5; // cl

  sprintf(igi2_frame.zTemp, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, retstr);
  v3 = igi2_frame.zTemp;
  v4 = InputBox_ptActiveInputBox->zInputString - igi2_frame.zTemp;
  do
  {
    v5 = *v3;
    v3[v4] = *v3;
    ++v3;
  }
  while ( v5 );
  igi2_frame.Rs.nResult = (int)retstr;
  igi2_frame.Rs.vResult = (double)(int)retstr;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy((void *)ltcg_ebx, &igi2_frame.Rs, 0x18u);
  return (struct Result_s *)ltcg_ebx;
}

// source: j/0/networkconfig.c:415  [anchor-mhash]
struct Result_s *__cdecl NetworkConfig_SetIntFromStringArg(
        struct Result_s *retstr,
        struct ArgList_s *ptArgList,
        int *pValue)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[16]; int ltcg_ebx[6]; };
    struct { char igi2_o2[40]; char zTemp[64]; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.zTemp[0] = 0;
      QVM_EvalArg(igi2_frame.zTemp, 64, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zTemp, 64);
    }
    scprintf(igi2_frame.zTemp, &g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, pValue);
  }
  qmemcpy(retstr, NetworkCommand_AnnounceInt((struct Result_s *)*pValue, igi2_frame.v5, (int)igi2_frame.ltcg_ebx), sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:437  [anchor-mhash]
struct Result_s *__cdecl NetworkConfig_SetIntFromIntArg(
        struct Result_s *retstr,
        struct ArgList_s *ptArgList,
        int *pValue)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[16]; int ltcg_ebx[6]; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptArgList && ptArgList->nArguments == 1 )
    *pValue = Script_EvalArgInt(ptArgList, 0);
  qmemcpy(retstr, NetworkCommand_AnnounceInt((struct Result_s *)*pValue, igi2_frame.v5, (int)igi2_frame.ltcg_ebx), sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:455  [anchor-caller]
struct Result_s *__cdecl NetworkConfig_SetFloatFromFloatArg(
        struct Result_s *retstr,
        struct ArgList_s *ptArgList,
        float *pValue)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v5; };
    struct { char igi2_o1[16]; int ltcg_ebx[6]; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptArgList && ptArgList->nArguments == 1 )
    *pValue = Script_EvalArgFloat(ptArgList, 0);
  qmemcpy(retstr, NetworkCommand_AnnounceFloat(*(struct Result_s **)pValue, igi2_frame.v5, (int)igi2_frame.ltcg_ebx), sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:474  [anchor-mhash]
struct Result_s *__cdecl NetworkConfig_SetBoolFromIntArg(
        struct Result_s *retstr,
        struct ArgList_s *ptArgList,
        enum bool *isValue)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s *v5; };
    struct { char igi2_o1[16]; int ltcg_ebx[6]; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptArgList && ptArgList->nArguments == 1 )
    *isValue = (char)Script_EvalArgInt(ptArgList, 0);
  qmemcpy(retstr, NetworkCommand_AnnounceBool(igi2_frame.v5, *isValue, (int)igi2_frame.ltcg_ebx), sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:491  [size]
struct Result_s *__cdecl ServerConfig_SetNameCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ServerConfig_tServerConfig.zServerName[0] = 0;
      QVM_EvalArg(&ServerConfig_tServerConfig, 64, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, ServerConfig_tServerConfig.zServerName, 64);
    }
  }
  NetworkCommand_SetEvalResponse(ServerConfig_tServerConfig.zServerName);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:510  [size]
struct Result_s *__cdecl ServerConfig_GetNameCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ServerConfig_s *v3; // eax
  int v4; // edx
  char v5; // cl
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  v3 = &ServerConfig_tServerConfig;
  v4 = InputBox_ptActiveInputBox->zInputString - (char *)&ServerConfig_tServerConfig;
  do
  {
    v5 = v3->zServerName[0];
    v3->zServerName[v4] = v3->zServerName[0];
    v3 = (struct ServerConfig_s *)((char *)v3 + 1);
  }
  while ( v5 );
  NetworkCommand_SetEvalResponse(ServerConfig_tServerConfig.zServerName);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:526  [size]
struct Result_s *__cdecl ServerConfig_SetPasswordCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ServerConfig_tServerConfig.zServerPassword[0] = 0;
      QVM_EvalArg(ServerConfig_tServerConfig.zServerPassword, 64, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, ServerConfig_tServerConfig.zServerPassword, 64);
    }
  }
  NetworkCommand_SetEvalResponse(ServerConfig_tServerConfig.zServerPassword);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:544  [size]
struct Result_s *__cdecl ServerConfig_GetPasswordCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  char *zServerPassword; // eax
  int v4; // edx
  char v5; // cl
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  zServerPassword = ServerConfig_tServerConfig.zServerPassword;
  v4 = InputBox_ptActiveInputBox->zInputString - ServerConfig_tServerConfig.zServerPassword;
  do
  {
    v5 = *zServerPassword;
    zServerPassword[v4] = *zServerPassword;
    ++zServerPassword;
  }
  while ( v5 );
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:558  [anchor-mhash]
struct Result_s *__cdecl ServerConfig_SetRConPassCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  char *zRConPassword; // edx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    zRConPassword = &g_zFileName.atSpriteResources[18].zResourceFilename[28];
    goto LABEL_14;
  }
LABEL_8:
  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ServerConfig_tServerConfig.zRConPassword[0] = 0;
      QVM_EvalArg(ServerConfig_tServerConfig.zRConPassword, 64, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, ServerConfig_tServerConfig.zRConPassword, 64);
    }
  }
  zRConPassword = ServerConfig_tServerConfig.zRConPassword;
LABEL_14:
  NetworkCommand_SetEvalResponse(zRConPassword);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:588  [anchor-mhash]
struct Result_s *__cdecl ServerConfig_SetMaxPlayersCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  int nSpectateMode; // eax
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    goto LABEL_11;
  }
LABEL_8:
  NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nSpectateMode);
  nSpectateMode = ServerConfig_tServerConfig.nSpectateMode;
  if ( ServerConfig_tServerConfig.nSpectateMode > 32 )
  {
    nSpectateMode = 32;
    ServerConfig_tServerConfig.nSpectateMode = 32;
  }
  v6.nResult = nSpectateMode;
  v6.vResult = (double)ServerConfig_tServerConfig.nSpectateMode;
LABEL_11:
  v6.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:594  [anchor-mhash]
struct Result_s *__cdecl ServerConfig_SetIntMaxPlayersCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // ebx
  __int32 isSuperUser; // eax
  int nSpectateMode; // eax
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    *(_QWORD *)&ltcg_ebx[2] = 0;
    goto LABEL_14;
  }
LABEL_8:
  if ( ptArgList && ptArgList->nArguments == 1 )
    ServerConfig_tServerConfig.nSpectateMode = Script_EvalArgInt(ptArgList, 0);
  NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nSpectateMode, v3, (int)ltcg_ebx);
  nSpectateMode = ServerConfig_tServerConfig.nSpectateMode;
  if ( ServerConfig_tServerConfig.nSpectateMode > 32 )
  {
    nSpectateMode = 32;
    ServerConfig_tServerConfig.nSpectateMode = 32;
  }
  ltcg_ebx[0] = nSpectateMode;
  *(double *)&ltcg_ebx[2] = (double)ServerConfig_tServerConfig.nSpectateMode;
LABEL_14:
  ltcg_ebx[4] = (int)&g_zInitialValue;
  qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:600  [size]
struct Result_s *__cdecl ServerConfig_GetMaxPlayersCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nSpectateMode, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_430C10(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nPort = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nPort, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_430CD0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nPort);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:620  [size~]
struct Result_s *__cdecl ServerConfig_SetPortCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nPort, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_430DB0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nClientPort = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nClientPort, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_430E70(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nClientPort);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:625  [size]
struct Result_s *__cdecl ServerConfig_GetPortCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nClientPort, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:640  [size]
struct Result_s *__cdecl ServerConfig_SetIntClientPortCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // edi
  struct Result_s *v4; // esi
  int ltcg_ebx[6]; // [esp+0h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
    ServerConfig_tServerConfig.nMaxPlayers = Script_EvalArgInt(ptArgList, 0);
  v4 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMaxPlayers, v3, (int)ltcg_ebx);
  qmemcpy(retstr, v4, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:645  [size]
struct Result_s *__cdecl ServerConfig_SetClientPortCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s *v3; // esi
  struct Result_s v5; // [esp+8h] [ebp-18h] BYREF

  v3 = NetworkConfig_SetIntFromStringArg(&v5, ptArgList, &ServerConfig_tServerConfig.nMaxPlayers);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:650  [size]
struct Result_s *__cdecl ServerConfig_GetClientPortCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMaxPlayers, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431000(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyStart);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4310B0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyStart = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyStart, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:677  [size]
struct Result_s *__cdecl ServerConfig_GetSpectateModeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyStart, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:690  [anchor-strings]
struct Result_s *__cdecl ServerConfig_FillSpectateModeListBoxCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  char *LocalizedStringForLanguage; // eax
  char *v4; // eax
  char *v5; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 &g_zFileName.atSpriteResources[18].zResourceFilename[20],
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ListBox_AddItem(LocalizedStringForLanguage, 0);
  v4 = Config_GetLocalizedStringForLanguage(
         &g_zFileName.atSpriteResources[18].zResourceFilename[8],
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v4, 1);
  v5 = Config_GetLocalizedStringForLanguage(
         &g_zFileName.atSpriteResources[18].zResourceFilename[4],
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v5, 2);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:707  [size]
struct Result_s *__cdecl ServerConfig_SetSpectateModeFromListCB(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  ServerConfig_tServerConfig.nMoneyStart = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:724  [size]
struct Result_s *__cdecl ServerConfig_GetSpecateModeFromListCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = ServerConfig_tServerConfig.nMoneyStart;
  Rs.vResult = (double)ServerConfig_tServerConfig.nMoneyStart;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431320(
        struct Result_s *a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.isPublic = (char)Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceBool(a1, ServerConfig_tServerConfig.isPublic, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:744  [size]
struct Result_s *__cdecl ServerConfig_GetTeamDamageCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = ServerConfig_tServerConfig.isPublic;
  Rs.vResult = (double)(int)ServerConfig_tServerConfig.isPublic;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431420(
        struct Result_s *a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.isForceFirstSpec = (char)Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceBool(a1, ServerConfig_tServerConfig.isForceFirstSpec, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:764  [size]
struct Result_s *__cdecl ServerConfig_GetForceFirstSpecCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = ServerConfig_tServerConfig.isForceFirstSpec;
  Rs.vResult = (double)(int)ServerConfig_tServerConfig.isForceFirstSpec;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431520(
        struct Result_s *a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nWarmup = (char)Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceBool(a1, (enum bool)ServerConfig_tServerConfig.nWarmup, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:784  [size]
struct Result_s *__cdecl ServerConfig_GetAutoBalanceCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = ServerConfig_tServerConfig.nWarmup;
  Rs.vResult = (double)ServerConfig_tServerConfig.nWarmup;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431620(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nPloss);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:829  [anchor-caller]
struct Result_s *__cdecl ServerConfig_SetIntWarmupCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[16]; _DWORD v6[6]; };
    struct { char igi2_o2[40]; int ltcg_ebx[6]; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int32 isSuperUser; // eax

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    igi2_frame.v6[0] = 0;
    igi2_frame.v6[2] = 0;
    igi2_frame.v6[3] = 0;
    igi2_frame.v6[4] = &g_zInitialValue;
    goto LABEL_12;
  }
LABEL_8:
  if ( ptArgList && ptArgList->nArguments == 1 )
    ServerConfig_tServerConfig.nPloss = Script_EvalArgInt(ptArgList, 0);
  qmemcpy(
    igi2_frame.v6,
    NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nPloss, igi2_frame.v5, (int)igi2_frame.ltcg_ebx),
    sizeof(igi2_frame.v6));
  NetMission_WarmupChangedFromCommand();
LABEL_12:
  qmemcpy(retstr, igi2_frame.v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:840  [size]
struct Result_s *__cdecl ServerConfig_GetWarmupCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nPloss, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4317D0(
        struct Result_s *a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.isAutoBalance = (char)Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceBool(a1, ServerConfig_tServerConfig.isAutoBalance, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:861  [size]
struct Result_s *__cdecl ServerConfig_GetPublicCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = ServerConfig_tServerConfig.isAutoBalance;
  Rs.vResult = (double)(int)ServerConfig_tServerConfig.isAutoBalance;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4318D0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyCap);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431980(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyCap = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyCap, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:885  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyStartCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyCap, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431A70(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyKill);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431B20(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyKill = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyKill, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:909  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyCapCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyKill, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431C10(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyTeamKill);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431CC0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyTeamKill = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyTeamKill, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:933  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyKillCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyTeamKill, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431DB0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyObjectivePlayerWin);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431E60(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyObjectivePlayerWin = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt(
         (struct Result_s *)ServerConfig_tServerConfig.nMoneyObjectivePlayerWin,
         a1,
         (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:957  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyTeamKillCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt(
         (struct Result_s *)ServerConfig_tServerConfig.nMoneyObjectivePlayerWin,
         igi2_frame.v5,
         (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_431F50(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyObjectiveTeamWin);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432000(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyObjectiveTeamWin = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt(
         (struct Result_s *)ServerConfig_tServerConfig.nMoneyObjectiveTeamWin,
         a1,
         (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:980  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyObjectivePlayerWinCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt(
         (struct Result_s *)ServerConfig_tServerConfig.nMoneyObjectiveTeamWin,
         igi2_frame.v5,
         (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4320F0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyObjectiveTeamLost);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4321A0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyObjectiveTeamLost = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt(
         (struct Result_s *)ServerConfig_tServerConfig.nMoneyObjectiveTeamLost,
         a1,
         (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1003  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyObjectiveTeamWinCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt(
         (struct Result_s *)ServerConfig_tServerConfig.nMoneyObjectiveTeamLost,
         igi2_frame.v5,
         (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432290(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyMissionWin);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432340(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyMissionWin = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyMissionWin, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1027  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyObjectiveTeamLostCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyMissionWin, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432430(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMoneyMissionLost);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4324E0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMoneyMissionLost = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyMissionLost, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1050  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyMissionWinCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMoneyMissionLost, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4325D0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMapMaxRounds);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432680(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMapMaxRounds = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMapMaxRounds, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1074  [size]
struct Result_s *__cdecl ServerConfig_GetMoneyMissionLostCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMapMaxRounds, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432770(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMapMaxTime);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432820(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMapMaxTime = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMapMaxTime, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1098  [size]
struct Result_s *__cdecl ServerConfig_GetMapMaxRoundsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMapMaxTime, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432910(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nMapMaxTeamScore);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4329C0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nMapMaxTeamScore = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nMapMaxTeamScore, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1122  [size]
struct Result_s *__cdecl ServerConfig_GetMapMaxTimeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nMapMaxTeamScore, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432AB0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nObjectiveMaxTime);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432B60(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nObjectiveMaxTime = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nObjectiveMaxTime, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1145  [size]
struct Result_s *__cdecl ServerConfig_GetMapMaxTeamScoreCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nObjectiveMaxTime, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432C50(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nBombTime);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432D00(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nBombTime = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nBombTime, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1168  [size]
struct Result_s *__cdecl ServerConfig_GetObjectiveMaxTimeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nBombTime, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432DF0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nSpawnMaxCost);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432EA0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nSpawnMaxCost = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nSpawnMaxCost, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1191  [size]
struct Result_s *__cdecl ServerConfig_GetBombTimeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nSpawnMaxCost, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_432F90(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nBombReposTime);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433040(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nBombReposTime = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nBombReposTime, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1214  [size]
struct Result_s *__cdecl ServerConfig_GetBombReposTimeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nBombReposTime, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433130(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nSpawnTimeToFree);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4331E0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nSpawnTimeToFree = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nSpawnTimeToFree, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1239  [size]
struct Result_s *__cdecl ServerConfig_GetSpawnMaxCostCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nSpawnTimeToFree, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4332D0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nSpawnSafeTime);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433380(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nSpawnSafeTime = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nSpawnSafeTime, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1263  [size]
struct Result_s *__cdecl ServerConfig_GetSpawnTimeToFreeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nSpawnSafeTime, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433470(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nTimeOut);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433520(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nTimeOut = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nTimeOut, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1286  [size]
struct Result_s *__cdecl ServerConfig_GetSpawnSafeTimeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nTimeOut, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1299  [anchor-strings]
struct Result_s *__cdecl ServerConfig_SetAllowSniperRiflesCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s *v3; // ebx
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
  {
    if ( ptArgList )
    {
      if ( ptArgList->nArguments == 1 )
        ServerConfig_tServerConfig.isAllowSniperRifles = (char)Script_EvalArgInt(ptArgList, 0);
    }
    qmemcpy(
      retstr,
      NetworkCommand_AnnounceBool(v3, ServerConfig_tServerConfig.isAllowSniperRifles, (int)ltcg_ebx),
      sizeof(struct Result_s));
    return retstr;
  }
  else
  {
    NetworkCommand_SetEvalResponse((char *)&g_zFileName.atSpriteResources[17].tSprite.nTextures);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
}

// source: j/0/networkconfig.c:1304  [size]
struct Result_s *__cdecl ServerConfig_GetAllowSniperRiflesCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt(
         (struct Result_s *)ServerConfig_tServerConfig.isAllowSniperRifles,
         igi2_frame.v5,
         (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1317  [size]
struct Result_s *__cdecl ClientConfig_SetPlayerNameCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ClientConfig_tClientConfig.zPlayerName[0] = 0;
      QVM_EvalArg(&ClientConfig_tClientConfig, 64, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, ClientConfig_tClientConfig.zPlayerName, 64);
    }
  }
  NetworkCommand_SetEvalResponse(ClientConfig_tClientConfig.zPlayerName);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1335  [size]
struct Result_s *__cdecl ClientConfig_GetPlayerNameCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ClientConfig_s *v3; // eax
  int v4; // edx
  char v5; // cl
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  v3 = &ClientConfig_tClientConfig;
  v4 = InputBox_ptActiveInputBox->zInputString - (char *)&ClientConfig_tClientConfig;
  do
  {
    v5 = v3->zPlayerName[0];
    v3->zPlayerName[v4] = v3->zPlayerName[0];
    v3 = (struct ClientConfig_s *)((char *)v3 + 1);
  }
  while ( v5 );
  NetworkCommand_SetEvalResponse(ClientConfig_tClientConfig.zPlayerName);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1351  [size]
struct Result_s *__cdecl ClientConfig_SetPlayerPasswordCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ClientConfig_tClientConfig.zPlayerPassword[0] = 0;
      QVM_EvalArg(ClientConfig_tClientConfig.zPlayerPassword, 64, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, ClientConfig_tClientConfig.zPlayerPassword, 64);
    }
  }
  NetworkCommand_SetEvalResponse(ClientConfig_tClientConfig.zPlayerPassword);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1369  [size]
struct Result_s *__cdecl ClientConfig_GetPlayerPasswordCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  char *zPlayerPassword; // eax
  int v4; // edx
  char v5; // cl
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  zPlayerPassword = ClientConfig_tClientConfig.zPlayerPassword;
  v4 = InputBox_ptActiveInputBox->zInputString - ClientConfig_tClientConfig.zPlayerPassword;
  do
  {
    v5 = *zPlayerPassword;
    zPlayerPassword[v4] = *zPlayerPassword;
    ++zPlayerPassword;
  }
  while ( v5 );
  NetworkCommand_SetEvalResponse(ClientConfig_tClientConfig.zPlayerPassword);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1483  [size]
struct Result_s *__cdecl ServerConfig_SetSmoothPercentCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s *v3; // esi
  struct Result_s v5; // [esp+8h] [ebp-18h] BYREF

  v3 = NetworkConfig_SetIntFromStringArg(&v5, ptArgList, (int *)&ServerConfig_tServerConfig.isTeamDamage);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1488  [size]
struct Result_s *__cdecl ServerConfig_SetIntSmoothPercentCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // edi
  struct Result_s *v4; // esi
  int ltcg_ebx[6]; // [esp+0h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
    ServerConfig_tServerConfig.isTeamDamage = Script_EvalArgInt(ptArgList, 0);
  v4 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.isTeamDamage, v3, (int)ltcg_ebx);
  qmemcpy(retstr, v4, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433940(struct Result_s *retstr)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v3; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v1; // esi

  v1 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.isTeamDamage, igi2_frame.v3, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v1, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433970(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, (int *)&pValue_84b73b4);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433A20(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      pValue_84b73b4 = (struct Result_s *)Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt(pValue_84b73b4, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433AE0(struct Result_s *retstr)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v3; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v1; // esi

  v1 = NetworkConfig_FillInputBoxInt(pValue_84b73b4, igi2_frame.v3, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v1, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433B10(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, (int *)&pValue_84b73b8);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_433BC0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      pValue_84b73b8 = (struct Result_s *)Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt(pValue_84b73b8, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1493  [size]
struct Result_s *__cdecl ServerConfig_GetSmoothPercentCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt(pValue_84b73b8, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1506  [anchor-mhash]
struct Result_s *__cdecl ClientConfig_SetBandwidthCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v7; };
    struct { char igi2_o1[12]; int v8; };
    struct { char igi2_o2[16]; int ltcg_ebx[6]; };
    struct { char igi2_o3[40]; char Buffer[64]; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int32 isSuperUser; // eax
  int v4; // ebx
  struct Result_s *v5; // esi

  if ( NetworkCommand_eEvalNetworkID != -1 )
  {
    if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      isSuperUser = NetworkCommand_eEvalNetworkID == 0;
    }
    else
    {
      if ( !NetworkCommand_eEvalNetworkID )
        goto LABEL_8;
      isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
    }
    if ( !isSuperUser )
    {
      NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
      goto LABEL_19;
    }
  }
LABEL_8:
  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.Buffer[0] = 0;
      QVM_EvalArg(igi2_frame.Buffer, 64, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.Buffer, 64);
    }
    scprintf(igi2_frame.Buffer, &g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, &igi2_frame.v8);
    v4 = igi2_frame.v8;
    if ( igi2_frame.v8 >= 0 )
    {
      if ( igi2_frame.v8 <= 1000 )
      {
LABEL_18:
        NetManager_SetLocalBandwidth(v4);
        ClientConfig_tClientConfig.nBandwidth = igi2_frame.v8;
        goto LABEL_19;
      }
      v4 = 1000;
    }
    else
    {
      v4 = 0;
    }
    igi2_frame.v8 = v4;
    goto LABEL_18;
  }
LABEL_19:
  v5 = NetworkCommand_AnnounceInt((struct Result_s *)ClientConfig_tClientConfig.nBandwidth, igi2_frame.v7, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1536  [anchor-mhash]
struct Result_s *__cdecl ClientConfig_SetIntBandwidthCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v8; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int32 isSuperUser; // eax
  int v4; // eax
  int v5; // ebx
  struct Result_s *v6; // esi

  if ( NetworkCommand_eEvalNetworkID != -1 )
  {
    if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      isSuperUser = NetworkCommand_eEvalNetworkID == 0;
    }
    else
    {
      if ( !NetworkCommand_eEvalNetworkID )
        goto LABEL_8;
      isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
    }
    if ( !isSuperUser )
    {
      NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
      goto LABEL_15;
    }
  }
LABEL_8:
  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v4 = Script_EvalArgInt(ptArgList, 0);
    v5 = v4;
    if ( v4 >= 0 )
    {
      if ( v4 > 1000 )
        v5 = 1000;
    }
    else
    {
      v5 = 0;
    }
    NetManager_SetLocalBandwidth(v5);
    ClientConfig_tClientConfig.nBandwidth = v5;
  }
LABEL_15:
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ClientConfig_tClientConfig.nBandwidth, igi2_frame.v8, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1558  [size]
struct Result_s *__cdecl ClientConfig_GetBandwidthCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ClientConfig_tClientConfig.nBandwidth, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1571  [anchor-strings]
struct Result_s *__cdecl ClientConfig_FillBandwidthListBoxCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int v3; // ebx
  struct ClientConfigBandwidthMode_s *v4; // esi
  char *LocalizedStringForLanguage; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = 0;
  if ( ClientConfig_nNumModes > 0 )
  {
    v4 = ClientConfig_atBandwidthMode;
    do
    {
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     v4->zName,
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      ListBox_AddItem(LocalizedStringForLanguage, v3++);
      ++v4;
    }
    while ( v3 < ClientConfig_nNumModes );
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1591  [anchor-mhash]
struct Result_s *__cdecl ClientConfig_SetBandwidthFromListCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  int nBandwidth; // eax
  _DWORD v7[6]; // [esp+8h] [ebp-18h] BYREF

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
  if ( (int)v4 >= 0 && (int)v4 < ClientConfig_nNumModes )
  {
    nBandwidth = ClientConfig_atBandwidthMode[(_DWORD)v4].nBandwidth;
    ClientConfig_tClientConfig.nBandwidth = nBandwidth;
    switch ( nBandwidth )
    {
      case 100:
        pValue_84b73b8 = (struct Result_s *)7;
        break;
      case 200:
        pValue_84b73b8 = (struct Result_s *)8;
        break;
      case 500:
        pValue_84b73b8 = (struct Result_s *)16;
        break;
      case 700:
        pValue_84b73b8 = (struct Result_s *)125;
        break;
    }
  }
  v7[0] = 0;
  v7[2] = 0;
  v7[3] = 0;
  v7[4] = &g_zInitialValue;
  qmemcpy(retstr, v7, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1617  [anchor-mhash]
struct Result_s *__cdecl ClientConfig_GetBandwidthFromListCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  int *p_nBandwidth; // ecx
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = 0;
  if ( ClientConfig_nNumModes <= 0 )
  {
LABEL_5:
    Rs.nResult = 0;
    Rs.vResult = 0.0;
  }
  else
  {
    p_nBandwidth = &ClientConfig_atBandwidthMode[0].nBandwidth;
    while ( ClientConfig_tClientConfig.nBandwidth != *p_nBandwidth )
    {
      ++v3;
      p_nBandwidth += 11;
      if ( v3 >= ClientConfig_nNumModes )
        goto LABEL_5;
    }
    Rs.nResult = v3;
    Rs.vResult = (double)v3;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434080(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nAutoKick);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434130(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nAutoKick = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nAutoKick, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1655  [size]
struct Result_s *__cdecl ServerConfig_GetTimeOutCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nAutoKick, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1668  [size]
struct Result_s *__cdecl ServerConfig_SetPacketLossCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s *v3; // esi
  struct Result_s v5; // [esp+8h] [ebp-18h] BYREF

  v3 = NetworkConfig_SetIntFromStringArg(&v5, ptArgList, (int *)&ServerConfig_tServerConfig.isLocalWeapon);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1673  [size]
struct Result_s *__cdecl ServerConfig_SetIntPacketLossCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // edi
  struct Result_s *v4; // esi
  int ltcg_ebx[6]; // [esp+0h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
    ServerConfig_tServerConfig.isLocalWeapon = Script_EvalArgInt(ptArgList, 0);
  v4 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.isLocalWeapon, v3, (int)ltcg_ebx);
  qmemcpy(retstr, v4, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1678  [size]
struct Result_s *__cdecl ServerConfig_GetPacketLossCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.isLocalWeapon, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4342D0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, (int *)&ServerConfig_tServerConfig.vSendDiffSpeed);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434380(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      LODWORD(ServerConfig_tServerConfig.vSendDiffSpeed) = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt(
         (struct Result_s *)LODWORD(ServerConfig_tServerConfig.vSendDiffSpeed),
         a1,
         (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1701  [size]
struct Result_s *__cdecl ServerConfig_GetAutoKickCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt(
         (struct Result_s *)LODWORD(ServerConfig_tServerConfig.vSendDiffSpeed),
         igi2_frame.v5,
         (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434470(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nPingMax);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434520(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nPingMax = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nPingMax, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1742  [size]
struct Result_s *__cdecl ServerConfig_GetPingMaxCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nPingMax, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434610(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nPlossMax);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4346C0(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nPlossMax = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nPlossMax, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1765  [size]
struct Result_s *__cdecl ServerConfig_GetPlossMaxCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nPlossMax, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4347B0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nIdleMax);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434860(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nIdleMax = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nIdleMax, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1788  [size]
struct Result_s *__cdecl ServerConfig_GetIdleMaxCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nIdleMax, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434950(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v5; // esi
  struct Result_s v6; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    v6.nResult = 0;
    v6.vResult = 0.0;
    v6.zResult = (char *)&g_zInitialValue;
    qmemcpy(retstr, &v6, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  v5 = NetworkConfig_SetIntFromStringArg(&v6, ptArgList, &ServerConfig_tServerConfig.nGoutMax);
  qmemcpy(retstr, v5, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_434A00(
        int a1,
        struct Result_s *retstr,
        void *a3,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  struct Result_s *v6; // esi
  int ltcg_ebx[6]; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_8;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_8;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse(&g_zFileName.atSpriteResources[18].zResourceFilename[28]);
    ltcg_ebx[0] = 0;
    ltcg_ebx[2] = 0;
    ltcg_ebx[3] = 0;
    ltcg_ebx[4] = (int)&g_zInitialValue;
    qmemcpy(retstr, ltcg_ebx, sizeof(struct Result_s));
    return retstr;
  }
LABEL_8:
  if ( ptArgList )
  {
    if ( ptArgList->nArguments == 1 )
      ServerConfig_tServerConfig.nGoutMax = Script_EvalArgInt(ptArgList, 0);
  }
  v6 = NetworkCommand_AnnounceInt((struct Result_s *)ServerConfig_tServerConfig.nGoutMax, a1, (int)ltcg_ebx);
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1811  [size]
struct Result_s *__cdecl ServerConfig_GetGoutMaxCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[12]; int ltcg_ebx[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Result_s *v3; // esi

  v3 = NetworkConfig_FillInputBoxInt((struct Result_s *)ServerConfig_tServerConfig.nGoutMax, igi2_frame.v5, (int)igi2_frame.ltcg_ebx);
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/networkconfig.c:1824  [anchor-hash]
void __cdecl NetworkConfig_Open()
{
  Symbol_Register(
    &g_zFileName.atSpriteResources[17].zResourceFilename[56],
    ServerConfig_SetNameCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[35].zResourceFilename[20],
    ServerConfig_SetNameCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[17].zResourceFilename[32],
    ServerConfig_GetNameCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[17].zResourceFilename[4],
    ServerConfig_SetPasswordCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[34].zResourceFilename[20],
    ServerConfig_SetPasswordCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[16].tSprite,
    ServerConfig_GetPasswordCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[16].zResourceFilename[36],
    ServerConfig_SetRConPassCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[33].zResourceFilename[32],
    ServerConfig_SetRConPassCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[16].zResourceFilename[12],
    sub_430CD0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[32].zResourceFilename[20],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_430C10,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[15].tSprite.ptQTilemap,
    ServerConfig_SetPortCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[15].zResourceFilename[48],
    sub_430E70,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[31].zResourceFilename[12],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_430DB0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[15].zResourceFilename[20],
    ServerConfig_GetPortCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[14].tSprite.nTextures,
    ServerConfig_SetClientPortCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[30].zResourceFilename[8],
    ServerConfig_SetIntClientPortCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[14].zResourceFilename[52],
    ServerConfig_GetClientPortCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[14].zResourceFilename[24],
    ServerConfig_SetMaxPlayersCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[29].tSprite.nQAnimframes,
    ServerConfig_SetIntMaxPlayersCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[13].tSprite.nQAnimframes,
    ServerConfig_GetMaxPlayersCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[13].zResourceFilename[52],
    sub_431000,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[29].tSprite.atQAnimframe,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4310B0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[13].zResourceFilename[20],
    ServerConfig_GetSpectateModeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[12].tSprite.atTexInfo,
    ServerConfig_FillSpectateModeListBoxCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[12].zResourceFilename[28],
    ServerConfig_SetSpectateModeFromListCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[11].tSprite.nTextures,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))ServerConfig_GetSpecateModeFromListCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[11].zResourceFilename[52],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431320,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[29].zResourceFilename[60],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431320,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[11].zResourceFilename[24],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))ServerConfig_GetTeamDamageCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[10].tSprite.nTextures,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431420,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[18].tSprite.nTextures,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431420,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[10].zResourceFilename[48],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))ServerConfig_GetForceFirstSpecCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[10].zResourceFilename[20],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431520,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[29].zResourceFilename[48],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431520,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[9].tSprite.nTextures,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))ServerConfig_GetAutoBalanceCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[9].zResourceFilename[56],
    sub_431620,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[29].zResourceFilename[40],
    ServerConfig_SetIntWarmupCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[9].zResourceFilename[32],
    ServerConfig_GetWarmupCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[9].zResourceFilename[8],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4317D0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[29].zResourceFilename[32],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4317D0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[8].tSprite.atQAnimframe,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))ServerConfig_GetPublicCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[8].zResourceFilename[44],
    sub_4318D0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[25].tSprite.nTextures,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431980,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[8].zResourceFilename[16],
    ServerConfig_GetMoneyStartCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[7].tSprite.ptQTilemap,
    sub_431A70,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[25].tSprite.atTexInfo,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431B20,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[7].zResourceFilename[48],
    ServerConfig_GetMoneyCapCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[7].zResourceFilename[20],
    sub_431C10,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[25].zResourceFilename[56],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431CC0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[6].tSprite.nTextures,
    ServerConfig_GetMoneyKillCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[6].zResourceFilename[48],
    sub_431DB0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[25].zResourceFilename[40],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_431E60,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[6].zResourceFilename[16],
    ServerConfig_GetMoneyTeamKillCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[5].tSprite,
    sub_431F50,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[25].zResourceFilename[20],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_432000,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[5].zResourceFilename[24],
    ServerConfig_GetMoneyObjectivePlayerWinCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[4].tSprite.atQAnimframe,
    sub_4320F0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[25].zResourceFilename[4],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4321A0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[4].zResourceFilename[32],
    ServerConfig_GetMoneyObjectiveTeamWinCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[3].tSprite.nTextures,
    sub_432290,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[24].tSprite.atQAnimframe,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_432340,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[3].zResourceFilename[40],
    ServerConfig_GetMoneyObjectiveTeamLostCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[3].zResourceFilename[8],
    sub_432430,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[24].zResourceFilename[56],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4324E0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[2].tSprite,
    ServerConfig_GetMoneyMissionWinCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[2].zResourceFilename[28],
    sub_4325D0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[24].zResourceFilename[36],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_432680,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[1].tSprite.nTextures,
    ServerConfig_GetMoneyMissionLostCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[1].zResourceFilename[48],
    sub_432770,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[23].zResourceFilename[16],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_432820,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[1].zResourceFilename[16],
    ServerConfig_GetMapMaxRoundsCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[0].tSprite.ptQTilemap,
    sub_432910,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[22].zResourceFilename[24],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4329C0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[0].zResourceFilename[48],
    ServerConfig_GetMapMaxTimeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[0].zResourceFilename[16],
    sub_432AB0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[21].zResourceFilename[8],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_432B60,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[15].zResourceFilename[52],
    ServerConfig_GetMapMaxTeamScoreCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[15].zResourceFilename[16],
    sub_432C50,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    g_zFileName.atSpriteResources[21].zResourceFilename,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_432D00,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[14].zResourceFilename[48],
    ServerConfig_GetObjectiveMaxTimeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[14].zResourceFilename[20],
    sub_432DF0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[20].tSprite.ptQTilemap,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_432EA0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[13].zResourceFilename[60],
    ServerConfig_GetBombTimeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[13].zResourceFilename[28],
    sub_432F90,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[19].zResourceFilename[8],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_433040,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atFontResources[12].ptFont,
    ServerConfig_GetBombReposTimeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[12].zResourceFilename[32],
    sub_433130,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[20].tSprite,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4331E0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    g_zFileName.atFontResources[12].zResourceFilename,
    ServerConfig_GetSpawnMaxCostCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[11].zResourceFilename[36],
    sub_4332D0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[20].zResourceFilename[52],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_433380,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[11].zResourceFilename[4],
    ServerConfig_GetSpawnTimeToFreeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[10].zResourceFilename[40],
    sub_433470,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[20].zResourceFilename[36],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_433520,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[10].zResourceFilename[8],
    ServerConfig_GetSpawnSafeTimeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[9].zResourceFilename[40],
    ServerConfig_SetAllowSniperRiflesCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[20].zResourceFilename[16],
    ServerConfig_SetAllowSniperRiflesCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[9].zResourceFilename[4],
    ServerConfig_GetAllowSniperRiflesCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[8].zResourceFilename[44],
    ClientConfig_SetPlayerNameCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[19].zResourceFilename[24],
    ClientConfig_SetPlayerNameCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[8].zResourceFilename[16],
    ClientConfig_GetPlayerNameCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[7].zResourceFilename[52],
    ClientConfig_SetPlayerPasswordCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[7].zResourceFilename[20],
    ClientConfig_GetPlayerPasswordCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[6].zResourceFilename[56],
    ServerConfig_SetSmoothPercentCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[20].zResourceFilename[8],
    ServerConfig_SetIntSmoothPercentCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[6].zResourceFilename[24],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_433940,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atFontResources[5].ptFont,
    sub_433970,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[19].tSprite,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_433A20,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[5].zResourceFilename[36],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_433AE0,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[5].zResourceFilename[12],
    sub_433B10,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[19].tSprite.ptQTilemap,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_433BC0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[4].zResourceFilename[56],
    ServerConfig_GetSmoothPercentCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[4].zResourceFilename[28],
    ClientConfig_SetBandwidthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[19].tSprite.nQAnimframes,
    ClientConfig_SetIntBandwidthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    g_zFileName.atFontResources[4].zResourceFilename,
    ClientConfig_GetBandwidthCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[3].zResourceFilename[32],
    ClientConfig_FillBandwidthListBoxCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atFontResources[2].ptFont,
    ClientConfig_SetBandwidthFromListCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[2].zResourceFilename[28],
    ClientConfig_GetBandwidthFromListCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[2].zResourceFilename[4],
    sub_434080,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[19].zResourceFilename[56],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_434130,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[1].zResourceFilename[48],
    ServerConfig_GetTimeOutCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[1].zResourceFilename[20],
    ServerConfig_SetPacketLossCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[19].zResourceFilename[36],
    ServerConfig_SetIntPacketLossCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[0].zResourceFilename[60],
    ServerConfig_GetPacketLossCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[0].zResourceFilename[32],
    sub_4342D0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[19].zResourceFilename[44],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_434380,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atFontResources[0].zResourceFilename[4],
    ServerConfig_GetAutoKickCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.apxLanguageResource[28],
    sub_434470,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[18].tSprite.atQAnimframe,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_434520,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.apxLanguageResource[22],
    ServerConfig_GetPingMaxCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.apxLanguageResource[15],
    sub_434610,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[18].zResourceFilename[60],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4346C0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.apxLanguageResource[8],
    ServerConfig_GetPlossMaxCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.apxLanguageResource[2],
    sub_4347B0,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[18].zResourceFilename[52],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_434860,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.zMenuResourcePath[248],
    ServerConfig_GetIdleMaxCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.zMenuResourcePath[224],
    sub_434950,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[18].zResourceFilename[44],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_434A00,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.zMenuResourcePath[200],
    ServerConfig_GetGoutMaxCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  ServerConfig_tServerConfig.tMapList.ptHead = (struct Node_s *)&ServerConfig_tServerConfig.tMapList.ptMiddle;
  ServerConfig_tServerConfig.tMapList.ptTail = (struct Node_s *)&ServerConfig_tServerConfig.tMapList;
  ServerConfig_tServerConfig.tMapList.ptMiddle = nullptr;
}

// source: j/0/networkconfig.c:2096  [anchor-hash]
void __cdecl NetworkConfig_Close()
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // ebx
  _DWORD **v2; // eax
  int v3; // esi

  ptHead = ServerConfig_tServerConfig.tMapList.ptHead;
  for ( i = ServerConfig_tServerConfig.tMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    v2 = Node_Remove(ptHead);
    if ( v2 )
    {
      v3 = *(_DWORD *)((unsigned int)(v2 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    ptHead = i;
  }
  Symbol_Remove(&g_zFileName.atSpriteResources[17].zResourceFilename[56]);
  Symbol_Remove(&g_zFileName.atSpriteResources[35].zResourceFilename[20]);
  Symbol_Remove(&g_zFileName.atSpriteResources[17].zResourceFilename[32]);
  Symbol_Remove(&g_zFileName.atSpriteResources[17].zResourceFilename[4]);
  Symbol_Remove(&g_zFileName.atSpriteResources[34].zResourceFilename[20]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[16].tSprite);
  Symbol_Remove(&g_zFileName.atSpriteResources[16].zResourceFilename[36]);
  Symbol_Remove(&g_zFileName.atSpriteResources[33].zResourceFilename[32]);
  Symbol_Remove(&g_zFileName.atSpriteResources[16].zResourceFilename[12]);
  Symbol_Remove(&g_zFileName.atSpriteResources[32].zResourceFilename[20]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[15].tSprite.ptQTilemap);
  Symbol_Remove(&g_zFileName.atSpriteResources[15].zResourceFilename[48]);
  Symbol_Remove(&g_zFileName.atSpriteResources[31].zResourceFilename[12]);
  Symbol_Remove(&g_zFileName.atSpriteResources[15].zResourceFilename[20]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[14].tSprite.nTextures);
  Symbol_Remove(&g_zFileName.atSpriteResources[30].zResourceFilename[8]);
  Symbol_Remove(&g_zFileName.atSpriteResources[14].zResourceFilename[52]);
  Symbol_Remove(&g_zFileName.atSpriteResources[14].zResourceFilename[24]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[29].tSprite.nQAnimframes);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[13].tSprite.nQAnimframes);
  Symbol_Remove(&g_zFileName.atSpriteResources[13].zResourceFilename[52]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[29].tSprite.atQAnimframe);
  Symbol_Remove(&g_zFileName.atSpriteResources[13].zResourceFilename[20]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[12].tSprite.atTexInfo);
  Symbol_Remove(&g_zFileName.atSpriteResources[12].zResourceFilename[28]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[11].tSprite.nTextures);
  Symbol_Remove(&g_zFileName.atSpriteResources[11].zResourceFilename[52]);
  Symbol_Remove(&g_zFileName.atSpriteResources[29].zResourceFilename[60]);
  Symbol_Remove(&g_zFileName.atSpriteResources[11].zResourceFilename[24]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[10].tSprite.nTextures);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[18].tSprite.nTextures);
  Symbol_Remove(&g_zFileName.atSpriteResources[10].zResourceFilename[48]);
  Symbol_Remove(&g_zFileName.atSpriteResources[10].zResourceFilename[20]);
  Symbol_Remove(&g_zFileName.atSpriteResources[29].zResourceFilename[48]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[9].tSprite.nTextures);
  Symbol_Remove(&g_zFileName.atSpriteResources[9].zResourceFilename[56]);
  Symbol_Remove(&g_zFileName.atSpriteResources[29].zResourceFilename[40]);
  Symbol_Remove(&g_zFileName.atSpriteResources[9].zResourceFilename[32]);
  Symbol_Remove(&g_zFileName.atSpriteResources[9].zResourceFilename[8]);
  Symbol_Remove(&g_zFileName.atSpriteResources[29].zResourceFilename[32]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[8].tSprite.atQAnimframe);
  Symbol_Remove(&g_zFileName.atSpriteResources[8].zResourceFilename[44]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[25].tSprite.nTextures);
  Symbol_Remove(&g_zFileName.atSpriteResources[8].zResourceFilename[16]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[7].tSprite.ptQTilemap);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[25].tSprite.atTexInfo);
  Symbol_Remove(&g_zFileName.atSpriteResources[7].zResourceFilename[48]);
  Symbol_Remove(&g_zFileName.atSpriteResources[7].zResourceFilename[20]);
  Symbol_Remove(&g_zFileName.atSpriteResources[25].zResourceFilename[56]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[6].tSprite.nTextures);
  Symbol_Remove(&g_zFileName.atSpriteResources[6].zResourceFilename[48]);
  Symbol_Remove(&g_zFileName.atSpriteResources[25].zResourceFilename[40]);
  Symbol_Remove(&g_zFileName.atSpriteResources[6].zResourceFilename[16]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[5].tSprite);
  Symbol_Remove(&g_zFileName.atSpriteResources[25].zResourceFilename[20]);
  Symbol_Remove(&g_zFileName.atSpriteResources[5].zResourceFilename[24]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[4].tSprite.atQAnimframe);
  Symbol_Remove(&g_zFileName.atSpriteResources[25].zResourceFilename[4]);
  Symbol_Remove(&g_zFileName.atSpriteResources[4].zResourceFilename[32]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[3].tSprite.nTextures);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[24].tSprite.atQAnimframe);
  Symbol_Remove(&g_zFileName.atSpriteResources[3].zResourceFilename[40]);
  Symbol_Remove(&g_zFileName.atSpriteResources[3].zResourceFilename[8]);
  Symbol_Remove(&g_zFileName.atSpriteResources[24].zResourceFilename[56]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[2].tSprite);
  Symbol_Remove(&g_zFileName.atSpriteResources[2].zResourceFilename[28]);
  Symbol_Remove(&g_zFileName.atSpriteResources[24].zResourceFilename[36]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[1].tSprite.nTextures);
  Symbol_Remove(&g_zFileName.atSpriteResources[1].zResourceFilename[48]);
  Symbol_Remove(&g_zFileName.atSpriteResources[23].zResourceFilename[16]);
  Symbol_Remove(&g_zFileName.atSpriteResources[1].zResourceFilename[16]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[0].tSprite.ptQTilemap);
  Symbol_Remove(&g_zFileName.atSpriteResources[22].zResourceFilename[24]);
  Symbol_Remove(&g_zFileName.atSpriteResources[0].zResourceFilename[48]);
  Symbol_Remove(&g_zFileName.atSpriteResources[0].zResourceFilename[16]);
  Symbol_Remove(&g_zFileName.atSpriteResources[21].zResourceFilename[8]);
  Symbol_Remove(&g_zFileName.atFontResources[15].zResourceFilename[52]);
  Symbol_Remove(&g_zFileName.atFontResources[15].zResourceFilename[16]);
  Symbol_Remove(g_zFileName.atSpriteResources[21].zResourceFilename);
  Symbol_Remove(&g_zFileName.atFontResources[14].zResourceFilename[48]);
  Symbol_Remove(&g_zFileName.atFontResources[14].zResourceFilename[20]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[20].tSprite.ptQTilemap);
  Symbol_Remove(&g_zFileName.atFontResources[13].zResourceFilename[60]);
  Symbol_Remove(&g_zFileName.atFontResources[13].zResourceFilename[28]);
  Symbol_Remove(&g_zFileName.atSpriteResources[19].zResourceFilename[8]);
  Symbol_Remove((char *)&g_zFileName.atFontResources[12].ptFont);
  Symbol_Remove(&g_zFileName.atFontResources[12].zResourceFilename[32]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[20].tSprite);
  Symbol_Remove(g_zFileName.atFontResources[12].zResourceFilename);
  Symbol_Remove(&g_zFileName.atFontResources[11].zResourceFilename[36]);
  Symbol_Remove(&g_zFileName.atSpriteResources[20].zResourceFilename[52]);
  Symbol_Remove(&g_zFileName.atFontResources[11].zResourceFilename[4]);
  Symbol_Remove(&g_zFileName.atFontResources[10].zResourceFilename[40]);
  Symbol_Remove(&g_zFileName.atSpriteResources[20].zResourceFilename[36]);
  Symbol_Remove(&g_zFileName.atFontResources[10].zResourceFilename[8]);
  Symbol_Remove(&g_zFileName.atFontResources[9].zResourceFilename[40]);
  Symbol_Remove(&g_zFileName.atSpriteResources[20].zResourceFilename[16]);
  Symbol_Remove(&g_zFileName.atFontResources[9].zResourceFilename[4]);
  Symbol_Remove(&g_zFileName.atFontResources[8].zResourceFilename[44]);
  Symbol_Remove(&g_zFileName.atSpriteResources[19].zResourceFilename[24]);
  Symbol_Remove(&g_zFileName.atFontResources[8].zResourceFilename[16]);
  Symbol_Remove(&g_zFileName.atFontResources[7].zResourceFilename[52]);
  Symbol_Remove(&g_zFileName.atFontResources[7].zResourceFilename[20]);
  Symbol_Remove(&g_zFileName.atFontResources[6].zResourceFilename[56]);
  Symbol_Remove(&g_zFileName.atSpriteResources[20].zResourceFilename[8]);
  Symbol_Remove(&g_zFileName.atFontResources[6].zResourceFilename[24]);
  Symbol_Remove((char *)&g_zFileName.atFontResources[5].ptFont);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[19].tSprite);
  Symbol_Remove(&g_zFileName.atFontResources[5].zResourceFilename[36]);
  Symbol_Remove(&g_zFileName.atFontResources[5].zResourceFilename[12]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[19].tSprite.ptQTilemap);
  Symbol_Remove(&g_zFileName.atFontResources[4].zResourceFilename[56]);
  Symbol_Remove(&g_zFileName.atFontResources[4].zResourceFilename[28]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[19].tSprite.nQAnimframes);
  Symbol_Remove(g_zFileName.atFontResources[4].zResourceFilename);
  Symbol_Remove(&g_zFileName.atFontResources[3].zResourceFilename[32]);
  Symbol_Remove((char *)&g_zFileName.atFontResources[2].ptFont);
  Symbol_Remove(&g_zFileName.atFontResources[2].zResourceFilename[28]);
  Symbol_Remove(&g_zFileName.atFontResources[2].zResourceFilename[4]);
  Symbol_Remove(&g_zFileName.atSpriteResources[19].zResourceFilename[56]);
  Symbol_Remove(&g_zFileName.atFontResources[1].zResourceFilename[48]);
  Symbol_Remove(&g_zFileName.atFontResources[1].zResourceFilename[20]);
  Symbol_Remove(&g_zFileName.atSpriteResources[19].zResourceFilename[36]);
  Symbol_Remove(&g_zFileName.atFontResources[0].zResourceFilename[60]);
  Symbol_Remove(&g_zFileName.atFontResources[0].zResourceFilename[32]);
  Symbol_Remove(&g_zFileName.atSpriteResources[19].zResourceFilename[44]);
  Symbol_Remove(&g_zFileName.atFontResources[0].zResourceFilename[4]);
  Symbol_Remove((char *)&g_zFileName.apxLanguageResource[28]);
  Symbol_Remove((char *)&g_zFileName.atSpriteResources[18].tSprite.atQAnimframe);
  Symbol_Remove((char *)&g_zFileName.apxLanguageResource[22]);
  Symbol_Remove((char *)&g_zFileName.apxLanguageResource[15]);
  Symbol_Remove(&g_zFileName.atSpriteResources[18].zResourceFilename[60]);
  Symbol_Remove((char *)&g_zFileName.apxLanguageResource[8]);
  Symbol_Remove((char *)&g_zFileName.apxLanguageResource[2]);
  Symbol_Remove(&g_zFileName.atSpriteResources[18].zResourceFilename[52]);
  Symbol_Remove(&g_zFileName.zMenuResourcePath[248]);
  Symbol_Remove(&g_zFileName.zMenuResourcePath[224]);
  Symbol_Remove(&g_zFileName.atSpriteResources[18].zResourceFilename[44]);
  Symbol_Remove(&g_zFileName.zMenuResourcePath[200]);
}
