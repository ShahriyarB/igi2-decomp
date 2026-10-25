/* j/0/human/soldiertypes/humansoldier.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/soldiertypes/humansoldier.c:133  [size]
void __cdecl CDAPFN0506_X_HumanSoldier_InitStateStandThrowGrenade()
{
  if ( !CDAPFN0506_HumanSoldier_InitStateStandThrowGrenade.Version )
    CDAPFN0506_X_HumanSoldier_InitStateStandThrowGrenade();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanSoldier_InitStateStandThrowGrenade.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanSoldier_InitStateStandThrowGrenade.FunctionAddress)();
}

// source: j/0/human/soldiertypes/humansoldier.c:294  [anchor-hash]
void __cdecl HumanSoldier_InitAnimStateIndexes()
{
  HumanSoldier_atStateData[10].iWeaponTypeAnim = 78;
  HumanSoldier_atStateData[17].iWeaponTypeAnim = 78;
  HumanSoldier_atStateData[18].iWeaponTypeAnim = 78;
  HumanSoldier_atStateData[5].iWeaponTypeAnim = 62;
  HumanSoldier_atStateData[23].iWeaponTypeAnim = 62;
  HumanSoldier_atStateData[32].iWeaponTypeAnim = 110;
  HumanSoldier_atStateData[34].iWeaponTypeAnim = 110;
  HumanSoldier_atStateData[0].iWeaponTypeAnim = 0;
  HumanSoldier_atStateData[2].iWeaponTypeAnim = 2;
  HumanSoldier_atStateData[1].iWeaponTypeAnim = 1;
  HumanSoldier_atStateData[3].iWeaponTypeAnim = 26;
  HumanSoldier_atStateData[4].iWeaponTypeAnim = 4;
  HumanSoldier_atStateData[6].iWeaponTypeAnim = 13;
  HumanSoldier_atStateData[7].iWeaponTypeAnim = 3;
  HumanSoldier_atStateData[8].iWeaponTypeAnim = 22;
  HumanSoldier_atStateData[9].iWeaponTypeAnim = 23;
  HumanSoldier_atStateData[11].iWeaponTypeAnim = 79;
  HumanSoldier_atStateData[12].iWeaponTypeAnim = 46;
  HumanSoldier_atStateData[13].iWeaponTypeAnim = 47;
  HumanSoldier_atStateData[14].iWeaponTypeAnim = 48;
  HumanSoldier_atStateData[15].iWeaponTypeAnim = 60;
  HumanSoldier_atStateData[16].iWeaponTypeAnim = 233;
  HumanSoldier_atStateData[19].iWeaponTypeAnim = 24;
  HumanSoldier_atStateData[20].iWeaponTypeAnim = 114;
  HumanSoldier_atStateData[21].iWeaponTypeAnim = 25;
  HumanSoldier_atStateData[22].iWeaponTypeAnim = 127;
  HumanSoldier_atStateData[24].iWeaponTypeAnim = 63;
  HumanSoldier_atStateData[25].iWeaponTypeAnim = 64;
  HumanSoldier_atStateData[26].iWeaponTypeAnim = 67;
  HumanSoldier_atStateData[27].iWeaponTypeAnim = 100;
  HumanSoldier_atStateData[28].iWeaponTypeAnim = 101;
  HumanSoldier_atStateData[29].iWeaponTypeAnim = 107;
  HumanSoldier_atStateData[30].iWeaponTypeAnim = 113;
  HumanSoldier_atStateData[31].iWeaponTypeAnim = 112;
  HumanSoldier_atStateData[33].iWeaponTypeAnim = 111;
  HumanSoldier_atStateData[35].iWeaponTypeAnim = 115;
  HumanSoldier_atStateData[36].iWeaponTypeAnim = 120;
  HumanSoldier_atStateData[37].iWeaponTypeAnim = 121;
  HumanSoldier_atStateData[38].iWeaponTypeAnim = 122;
  HumanSoldier_atStateData[39].iWeaponTypeAnim = 0;
  HumanSoldier_atStateData[40].iWeaponTypeAnim = 238;
  HumanSoldier_atStateData[41].iWeaponTypeAnim = 143;
  HumanSoldier_atStateData[42].iWeaponTypeAnim = 126;
  HumanSoldier_atStateData[43].iWeaponTypeAnim = 187;
  HumanSoldier_atStateData[44].iWeaponTypeAnim = 188;
  HumanSoldier_atStateData[45].iWeaponTypeAnim = 189;
  HumanSoldier_atStateData[46].iWeaponTypeAnim = 190;
  HumanSoldier_atStateData[47].iWeaponTypeAnim = 191;
  HumanSoldier_atStateData[49].iWeaponTypeAnim = 193;
  HumanSoldier_atStateData[50].iWeaponTypeAnim = 194;
  HumanSoldier_atStateData[51].iWeaponTypeAnim = 195;
  HumanSoldier_atStateData[52].iWeaponTypeAnim = 196;
  HumanSoldier_atStateData[53].iWeaponTypeAnim = 197;
  HumanSoldier_atStateData[54].iWeaponTypeAnim = 198;
  HumanSoldier_atStateData[55].iWeaponTypeAnim = 199;
  HumanSoldier_atStateData[56].iWeaponTypeAnim = 200;
  HumanSoldier_atStateData[57].iWeaponTypeAnim = 201;
  HumanSoldier_atStateData[58].iWeaponTypeAnim = 202;
  HumanSoldier_atStateData[59].iWeaponTypeAnim = 203;
  HumanSoldier_atStateData[60].iWeaponTypeAnim = 204;
  HumanSoldier_atStateData[61].iWeaponTypeAnim = 205;
  HumanSoldier_atStateData[62].iWeaponTypeAnim = 206;
  HumanSoldier_atStateData[48].iWeaponTypeAnim = 207;
  HumanSoldier_atStateData[64].iWeaponTypeAnim = 208;
  HumanSoldier_atStateData[65].iWeaponTypeAnim = 209;
  HumanSoldier_atStateData[66].iWeaponTypeAnim = 210;
  HumanSoldier_atStateData[67].iWeaponTypeAnim = 211;
  HumanSoldier_atStateData[68].iWeaponTypeAnim = 212;
  HumanSoldier_atStateData[69].iWeaponTypeAnim = 213;
  HumanSoldier_atStateData[70].iWeaponTypeAnim = 214;
  HumanSoldier_atStateData[71].iWeaponTypeAnim = 215;
  HumanSoldier_atStateData[72].iWeaponTypeAnim = 216;
  HumanSoldier_atStateData[73].iWeaponTypeAnim = 217;
  HumanSoldier_atStateData[74].iWeaponTypeAnim = 218;
  HumanSoldier_atStateData[75].iWeaponTypeAnim = 219;
  HumanSoldier_atStateData[76].iWeaponTypeAnim = 220;
  HumanSoldier_atStateData[77].iWeaponTypeAnim = 221;
  HumanSoldier_atStateData[78].iWeaponTypeAnim = 222;
  HumanSoldier_atStateData[79].iWeaponTypeAnim = 223;
  HumanSoldier_atStateData[80].iWeaponTypeAnim = 224;
  HumanSoldier_atStateData[81].iWeaponTypeAnim = 225;
  HumanSoldier_atStateData[82].iWeaponTypeAnim = 226;
  HumanSoldier_atStateData[83].iWeaponTypeAnim = 227;
  HumanSoldier_atStateData[84].iWeaponTypeAnim = 0;
  HumanSoldier_atStateData[85].iWeaponTypeAnim = 21;
  HumanSoldier_atStateData[86].iWeaponTypeAnim = 0;
  HumanSoldier_atStateData[87].iWeaponTypeAnim = 151;
  HumanSoldier_atStateData[88].iWeaponTypeAnim = 159;
  HumanSoldier_atStateData[89].iWeaponTypeAnim = 147;
  HumanSoldier_atStateData[90].iWeaponTypeAnim = 155;
  HumanSoldier_atStateData[91].iWeaponTypeAnim = 143;
  HumanSoldier_atStateData[92].iWeaponTypeAnim = 52;
  HumanSoldier_atStateData[93].iWeaponTypeAnim = 117;
  HumanSoldier_atStateData[94].iWeaponTypeAnim = 163;
  HumanSoldier_atStateData[95].iWeaponTypeAnim = 54;
  HumanSoldier_atStateData[96].iWeaponTypeAnim = 55;
  HumanSoldier_atStateData[97].iWeaponTypeAnim = 56;
  HumanSoldier_atStateData[98].iWeaponTypeAnim = 57;
  HumanSoldier_atStateData[99].iWeaponTypeAnim = 58;
  HumanSoldier_atStateData[100].iWeaponTypeAnim = 59;
  HumanSoldier_atStateData[101].iWeaponTypeAnim = 120;
  HumanSoldier_atStateData[102].iWeaponTypeAnim = 60;
  HumanSoldier_atStateData[103].iWeaponTypeAnim = 61;
  HumanSoldier_atStateData[104].iWeaponTypeAnim = 34;
  HumanSoldier_atStateData[105].iWeaponTypeAnim = 35;
  HumanSoldier_atStateData[106].iWeaponTypeAnim = 36;
  HumanSoldier_atStateData[107].iWeaponTypeAnim = 37;
  HumanSoldier_atStateData[108].iWeaponTypeAnim = 38;
  HumanSoldier_atStateData[109].iWeaponTypeAnim = 39;
  HumanSoldier_atStateData[110].iWeaponTypeAnim = 40;
  HumanSoldier_atStateData[111].iWeaponTypeAnim = 41;
  HumanSoldier_atStateData[112].iWeaponTypeAnim = 42;
  HumanSoldier_atStateData[113].iWeaponTypeAnim = 43;
  HumanSoldier_atStateData[114].iWeaponTypeAnim = 44;
  HumanSoldier_atStateData[115].iWeaponTypeAnim = 144;
  HumanSoldier_atStateData[116].iWeaponTypeAnim = 145;
  HumanSoldier_atStateData[117].iWeaponTypeAnim = 146;
  HumanSoldier_atStateData[118].iWeaponTypeAnim = 148;
  HumanSoldier_atStateData[119].iWeaponTypeAnim = 149;
  HumanSoldier_atStateData[120].iWeaponTypeAnim = 150;
  HumanSoldier_atStateData[121].iWeaponTypeAnim = 152;
  HumanSoldier_atStateData[122].iWeaponTypeAnim = 153;
  HumanSoldier_atStateData[123].iWeaponTypeAnim = 154;
  HumanSoldier_atStateData[124].iWeaponTypeAnim = 156;
  HumanSoldier_atStateData[125].iWeaponTypeAnim = 157;
  HumanSoldier_atStateData[126].iWeaponTypeAnim = 158;
  HumanSoldier_atStateData[127].iWeaponTypeAnim = 160;
  HumanSoldier_atStateData[128].iWeaponTypeAnim = 161;
  HumanSoldier_atStateData[129].iWeaponTypeAnim = 162;
  HumanSoldier_atStateData[130].iWeaponTypeAnim = 164;
  HumanSoldier_atStateData[131].iWeaponTypeAnim = 165;
  HumanSoldier_atStateData[132].iWeaponTypeAnim = 166;
  HumanSoldier_atStateData[133].iWeaponTypeAnim = 167;
  HumanSoldier_atStateData[134].iWeaponTypeAnim = 168;
  HumanSoldier_atStateData[135].iWeaponTypeAnim = 169;
  HumanSoldier_atStateData[136].iWeaponTypeAnim = 170;
  HumanSoldier_atStateData[137].iWeaponTypeAnim = 171;
  HumanSoldier_atStateData[138].iWeaponTypeAnim = 172;
  HumanSoldier_atStateData[139].iWeaponTypeAnim = 173;
  HumanSoldier_atStateData[140].iWeaponTypeAnim = 174;
  HumanSoldier_atStateData[141].iWeaponTypeAnim = 175;
  HumanSoldier_atStateData[142].iWeaponTypeAnim = 176;
  HumanSoldier_atStateData[143].iWeaponTypeAnim = 177;
  HumanSoldier_atStateData[144].iWeaponTypeAnim = 178;
  HumanSoldier_atStateData[145].iWeaponTypeAnim = 183;
  HumanSoldier_atStateData[146].iWeaponTypeAnim = 184;
  HumanSoldier_atStateData[147].iWeaponTypeAnim = 185;
  HumanSoldier_atStateData[148].iWeaponTypeAnim = 186;
  HumanSoldier_atStateData[149].iWeaponTypeAnim = 179;
  HumanSoldier_atStateData[150].iWeaponTypeAnim = 180;
  HumanSoldier_atStateData[151].iWeaponTypeAnim = 181;
  HumanSoldier_atStateData[152].iWeaponTypeAnim = 182;
}

// source: j/0/human/soldiertypes/humansoldier.c:499  [anchor-hash]
void __cdecl HumanSoldier_InitStateFunctions()
{
  memset(HumanSoldier_apfExitState, 0, sizeof(HumanSoldier_apfExitState));
  HumanSoldier_apfState[43] = HumanSoldier_InitStateLieDownDie;
  HumanSoldier_apfState[44] = HumanSoldier_InitStateLieDownDie;
  HumanSoldier_apfState[45] = HumanSoldier_InitStateLieDownDie;
  HumanSoldier_apfState[46] = HumanSoldier_InitStateLieDownDie;
  HumanSoldier_apfState[47] = HumanSoldier_InitStateLieDownDie;
  HumanSoldier_apfState[48] = HumanSoldier_InitStateLieDownDie;
  HumanSoldier_apfState[49] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[50] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[51] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[52] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[53] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[54] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[55] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[56] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[57] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[58] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[59] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[60] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[61] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[62] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[63] = HumanSoldier_InitStateKneelDie;
  HumanSoldier_apfState[0] = HumanSoldier_InitStateStand;
  HumanSoldier_apfState[2] = nullptr;
  HumanSoldier_apfState[1] = HumanSoldier_InitStateStandTurn;
  HumanSoldier_apfState[3] = HumanSoldier_InitStatePanicForward;
  HumanSoldier_apfState[5] = HumanSoldier_InitStateRunForward;
  HumanSoldier_apfState[4] = nullptr;
  HumanSoldier_apfState[6] = HumanSoldier_InitStateWalkForward;
  HumanSoldier_apfState[8] = HumanSoldier_InitStateStandRollLeft;
  HumanSoldier_apfState[9] = HumanSoldier_InitStateStandRollRight;
  HumanSoldier_apfState[10] = nullptr;
  HumanSoldier_apfState[11] = nullptr;
  HumanSoldier_apfState[12] = HumanSoldier_InitStateStandThrowGrenade;
  HumanSoldier_apfState[13] = nullptr;
  HumanSoldier_apfState[14] = HumanSoldier_InitStateStandCloseCombat;
  HumanSoldier_apfState[15] = nullptr;
  HumanSoldier_apfState[16] = nullptr;
  HumanSoldier_apfState[17] = nullptr;
  HumanSoldier_apfState[18] = nullptr;
  HumanSoldier_apfState[19] = HumanSoldier_InitStateStandToKneel;
  HumanSoldier_apfState[20] = HumanSoldier_InitStateKneelToStand;
  HumanSoldier_apfState[21] = HumanSoldier_InitStateStandToLieDown;
  HumanSoldier_apfState[22] = HumanSoldier_InitStateLieDownToStand;
  HumanSoldier_apfState[23] = HumanSoldier_InitStateTenseRunForward;
  HumanSoldier_apfState[24] = HumanSoldier_InitStateTenseRunLeft;
  HumanSoldier_apfState[25] = HumanSoldier_InitStateTenseRunRight;
  HumanSoldier_apfState[26] = HumanSoldier_InitStateTenseRunBackward;
  HumanSoldier_apfState[27] = HumanSoldier_InitStateKneel;
  HumanSoldier_apfState[28] = nullptr;
  HumanSoldier_apfState[29] = HumanSoldier_InitStateKneelTurn;
  HumanSoldier_apfState[30] = HumanSoldier_InitStateKneelRollLeft;
  HumanSoldier_apfState[31] = HumanSoldier_InitStateKneelRollRight;
  HumanSoldier_apfState[32] = nullptr;
  HumanSoldier_apfState[33] = nullptr;
  HumanSoldier_apfState[34] = nullptr;
  HumanSoldier_apfState[35] = HumanSoldier_InitStateKneelToLieDown;
  HumanSoldier_apfState[36] = HumanSoldier_InitStateLieDown;
  HumanSoldier_apfState[37] = HumanSoldier_InitStateLieDownFire;
  HumanSoldier_apfState[38] = HumanSoldier_InitStateLieDownReload;
  HumanSoldier_apfState[39] = HumanSoldier_InitStateFall;
  HumanSoldier_apfState[40] = HumanSoldier_InitStateSilentKill;
  HumanSoldier_apfState[64] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[65] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[66] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[67] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[68] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[69] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[70] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[71] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[72] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[73] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[74] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[75] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[76] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[77] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[78] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[79] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[80] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[81] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[82] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[83] = HumanSoldier_InitStateDie;
  HumanSoldier_apfState[84] = HumanSoldier_InitStateStandAction;
  HumanSoldier_apfState[85] = HumanSoldier_InitStateStationaryGun;
  HumanSoldier_apfState[86] = HumanSoldier_InitStateDoor;
  HumanSoldier_apfState[92] = nullptr;
  HumanSoldier_apfState[93] = nullptr;
  HumanSoldier_apfState[95] = nullptr;
  HumanSoldier_apfState[96] = nullptr;
  HumanSoldier_apfState[97] = nullptr;
  HumanSoldier_apfState[98] = nullptr;
  HumanSoldier_apfState[99] = nullptr;
  HumanSoldier_apfState[100] = HumanSoldier_InitStateStandPressSwitch;
  HumanSoldier_apfState[101] = HumanSoldier_InitStateDead;
  HumanSoldier_apfState[102] = HumanSoldier_InitStateStand;
  HumanSoldier_apfState[103] = nullptr;
  HumanSoldier_apfState[104] = nullptr;
  HumanSoldier_apfState[105] = nullptr;
  HumanSoldier_apfState[106] = nullptr;
  HumanSoldier_apfState[107] = nullptr;
  HumanSoldier_apfState[108] = nullptr;
  HumanSoldier_apfState[109] = nullptr;
  HumanSoldier_apfState[110] = nullptr;
  HumanSoldier_apfState[111] = nullptr;
  HumanSoldier_apfState[112] = nullptr;
  HumanSoldier_apfState[113] = nullptr;
  HumanSoldier_apfState[114] = nullptr;
  HumanSoldier_apfState[41] = HumanSoldier_InitStateHit;
  HumanSoldier_apfState[42] = HumanSoldier_InitStateLieDownHit;
  HumanSoldier_apfState[94] = nullptr;
  HumanSoldier_apfState[91] = nullptr;
  HumanSoldier_apfState[115] = nullptr;
  HumanSoldier_apfState[116] = nullptr;
  HumanSoldier_apfState[117] = nullptr;
  HumanSoldier_apfState[89] = nullptr;
  HumanSoldier_apfState[118] = nullptr;
  HumanSoldier_apfState[119] = nullptr;
  HumanSoldier_apfState[120] = nullptr;
  HumanSoldier_apfState[87] = nullptr;
  HumanSoldier_apfState[121] = nullptr;
  HumanSoldier_apfState[122] = nullptr;
  HumanSoldier_apfState[123] = nullptr;
  HumanSoldier_apfState[90] = nullptr;
  HumanSoldier_apfState[124] = nullptr;
  HumanSoldier_apfState[125] = nullptr;
  HumanSoldier_apfState[126] = nullptr;
  HumanSoldier_apfState[88] = nullptr;
  HumanSoldier_apfState[127] = nullptr;
  HumanSoldier_apfState[128] = nullptr;
  HumanSoldier_apfState[129] = nullptr;
  HumanSoldier_apfState[130] = nullptr;
  HumanSoldier_apfState[131] = nullptr;
  HumanSoldier_apfState[132] = nullptr;
  HumanSoldier_apfState[133] = nullptr;
  HumanSoldier_apfState[134] = nullptr;
  HumanSoldier_apfState[135] = nullptr;
  HumanSoldier_apfState[136] = nullptr;
  HumanSoldier_apfState[137] = nullptr;
  HumanSoldier_apfState[138] = nullptr;
  HumanSoldier_apfState[139] = nullptr;
  HumanSoldier_apfState[140] = nullptr;
  HumanSoldier_apfState[141] = nullptr;
  HumanSoldier_apfState[142] = nullptr;
  HumanSoldier_apfState[143] = nullptr;
  HumanSoldier_apfState[144] = nullptr;
  HumanSoldier_apfState[145] = nullptr;
  HumanSoldier_apfState[146] = nullptr;
  HumanSoldier_apfState[147] = nullptr;
  HumanSoldier_apfState[148] = nullptr;
  HumanSoldier_apfState[149] = nullptr;
  HumanSoldier_apfState[150] = nullptr;
  HumanSoldier_apfState[151] = nullptr;
  HumanSoldier_apfState[152] = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:681  [anchor-mhash]
void __cdecl HumanSoldier_InitDamagePartTable()
{
  int *p_eLongHitState; // eax
  int v1; // ebx
  bool v2; // cc
  int v3; // ebx
  struct QTask_s **p_ptPrev; // [esp+10h] [ebp-14h]
  int v5; // [esp+14h] [ebp-10h]
  _DWORD *v6; // [esp+18h] [ebp-Ch]
  int v7; // [esp+18h] [ebp-Ch]
  int v8; // [esp+1Ch] [ebp-8h]
  int iDamagePart; // [esp+20h] [ebp-4h]
  _DWORD *iDamageParta; // [esp+20h] [ebp-4h]

  p_ptPrev = &HumanAIConfig_ptHumanAIConfigQTask[1].ptPrev;
  v8 = 0;
  p_eLongHitState = &HumanSoldier_aatDamagePartData[0][0].eLongHitState;
  do
  {
    if ( *p_ptPrev )
    {
      iDamagePart = 0;
      v5 = 712;
      v6 = p_eLongHitState + 14;
      do
      {
        *(v6 - 15) = *(_DWORD *)((char *)*p_ptPrev + v5 - 4);
        *v6 = *(struct QTask_s **)((char *)&(*p_ptPrev)->ptNext + v5);
        v6[15] = *(struct QTask_s **)((char *)&(*p_ptPrev)->ptPrev + v5);
        v6[30] = *(struct QTask_s **)((char *)&(*p_ptPrev)->tQTaskChildren.ptHead + v5);
        v6[45] = *(struct QTask_s **)((char *)&(*p_ptPrev)->tQTaskChildren.ptMiddle + v5);
        v6[60] = *(struct QTask_s **)((char *)&(*p_ptPrev)->tQTaskChildren.ptTail + v5);
        v6[75] = *(struct QReference_s **)((char *)&(*p_ptPrev)->tQTaskRefList.ptHead + v5);
        v6[90] = *(struct QReference_s **)((char *)&(*p_ptPrev)->tQTaskRefList.ptMiddle + v5);
        v5 += 32;
        v1 = iDamagePart + 8;
        v2 = iDamagePart + 8 < 10;
        iDamagePart += 8;
        v6 += 120;
      }
      while ( v2 );
      if ( v1 < 17 )
      {
        v7 = 4 * v1 + 708;
        iDamageParta = (_DWORD *)(60 * (v8 + v1) + 139173824);
        v3 = v7;
        do
        {
          *iDamageParta = *(struct QTask_s **)((char *)&(*p_ptPrev)->ptNext + v3);
          v3 = v7 + 4;
          v2 = v7 + 4 < 776;
          v7 += 4;
          iDamageParta += 15;
        }
        while ( v2 );
      }
      *p_eLongHitState = 87;
      p_eLongHitState[1] = 121;
      p_eLongHitState[2] = 122;
      p_eLongHitState[3] = 123;
      p_eLongHitState[4] = 71;
      p_eLongHitState[5] = 72;
      p_eLongHitState[6] = 73;
      p_eLongHitState[7] = 136;
      p_eLongHitState[8] = 137;
      p_eLongHitState[9] = 138;
      p_eLongHitState[10] = 149;
      p_eLongHitState[11] = 150;
      p_eLongHitState[12] = 151;
      p_eLongHitState[13] = 152;
      p_eLongHitState[15] = 87;
      p_eLongHitState[16] = 121;
      p_eLongHitState[17] = 122;
      p_eLongHitState[18] = 123;
      p_eLongHitState[19] = 71;
      p_eLongHitState[20] = 72;
      p_eLongHitState[21] = 74;
      p_eLongHitState[22] = 136;
      p_eLongHitState[23] = 137;
      p_eLongHitState[24] = 138;
      p_eLongHitState[25] = 149;
      p_eLongHitState[26] = 150;
      p_eLongHitState[27] = 151;
      p_eLongHitState[28] = 152;
      p_eLongHitState[30] = 87;
      p_eLongHitState[31] = 121;
      p_eLongHitState[32] = 122;
      p_eLongHitState[33] = 123;
      p_eLongHitState[34] = 71;
      p_eLongHitState[35] = 72;
      p_eLongHitState[36] = 73;
      p_eLongHitState[37] = 136;
      p_eLongHitState[38] = 137;
      p_eLongHitState[39] = 138;
      p_eLongHitState[40] = 149;
      p_eLongHitState[41] = 150;
      p_eLongHitState[42] = 151;
      p_eLongHitState[43] = 152;
      p_eLongHitState[45] = 88;
      p_eLongHitState[46] = 127;
      p_eLongHitState[47] = 128;
      p_eLongHitState[48] = 129;
      p_eLongHitState[49] = 71;
      p_eLongHitState[50] = 73;
      p_eLongHitState[52] = 142;
      p_eLongHitState[53] = 143;
      p_eLongHitState[54] = 144;
      p_eLongHitState[55] = -1;
      p_eLongHitState[56] = -1;
      p_eLongHitState[57] = -1;
      p_eLongHitState[58] = -1;
      p_eLongHitState[60] = 88;
      p_eLongHitState[61] = 127;
      p_eLongHitState[62] = 128;
      p_eLongHitState[63] = 129;
      p_eLongHitState[64] = 71;
      p_eLongHitState[65] = 72;
      p_eLongHitState[66] = 73;
      p_eLongHitState[67] = 142;
      p_eLongHitState[68] = 143;
      p_eLongHitState[69] = 144;
      p_eLongHitState[70] = -1;
      p_eLongHitState[71] = -1;
      p_eLongHitState[72] = -1;
      p_eLongHitState[73] = -1;
      p_eLongHitState[75] = 88;
      p_eLongHitState[76] = 127;
      p_eLongHitState[77] = 128;
      p_eLongHitState[78] = 129;
      p_eLongHitState[79] = 71;
      p_eLongHitState[80] = 72;
      p_eLongHitState[81] = 73;
      p_eLongHitState[82] = 142;
      p_eLongHitState[83] = 143;
      p_eLongHitState[84] = 144;
      p_eLongHitState[85] = -1;
      p_eLongHitState[86] = -1;
      p_eLongHitState[87] = -1;
      p_eLongHitState[88] = -1;
      p_eLongHitState[90] = 89;
      p_eLongHitState[91] = 118;
      p_eLongHitState[92] = 119;
      p_eLongHitState[93] = 120;
      p_eLongHitState[94] = 74;
      p_eLongHitState[95] = 75;
      p_eLongHitState[96] = 76;
      p_eLongHitState[97] = 133;
      p_eLongHitState[98] = 134;
      p_eLongHitState[99] = 135;
      p_eLongHitState[100] = 145;
      p_eLongHitState[101] = 146;
      p_eLongHitState[102] = 147;
      p_eLongHitState[103] = 148;
      p_eLongHitState[105] = 89;
      p_eLongHitState[106] = 118;
      p_eLongHitState[107] = 119;
      p_eLongHitState[108] = 120;
      p_eLongHitState[109] = 74;
      p_eLongHitState[110] = 75;
      p_eLongHitState[111] = 76;
      p_eLongHitState[112] = 133;
      p_eLongHitState[113] = 134;
      p_eLongHitState[114] = 135;
      p_eLongHitState[115] = 145;
      p_eLongHitState[116] = 146;
      p_eLongHitState[117] = 147;
      p_eLongHitState[118] = 148;
      p_eLongHitState[120] = 89;
      p_eLongHitState[121] = 118;
      p_eLongHitState[122] = 119;
      p_eLongHitState[123] = 120;
      p_eLongHitState[124] = 74;
      p_eLongHitState[125] = 75;
      p_eLongHitState[126] = 76;
      p_eLongHitState[127] = 133;
      p_eLongHitState[128] = 134;
      p_eLongHitState[129] = 135;
      p_eLongHitState[130] = 145;
      p_eLongHitState[131] = 146;
      p_eLongHitState[132] = 147;
      p_eLongHitState[133] = 148;
      p_eLongHitState[135] = 90;
      p_eLongHitState[136] = 124;
      p_eLongHitState[137] = 125;
      p_eLongHitState[138] = 126;
      p_eLongHitState[139] = 74;
      p_eLongHitState[140] = 75;
      p_eLongHitState[141] = 76;
      p_eLongHitState[142] = 139;
      p_eLongHitState[143] = 140;
      p_eLongHitState[144] = 141;
      p_eLongHitState[145] = -1;
      p_eLongHitState[146] = -1;
      p_eLongHitState[147] = -1;
      p_eLongHitState[148] = -1;
      p_eLongHitState[150] = 90;
      p_eLongHitState[151] = 124;
      p_eLongHitState[152] = 125;
      p_eLongHitState[153] = 126;
      p_eLongHitState[154] = 74;
      p_eLongHitState[155] = 75;
      p_eLongHitState[156] = 76;
      p_eLongHitState[157] = 139;
      p_eLongHitState[158] = 140;
      p_eLongHitState[159] = 141;
      p_eLongHitState[160] = -1;
      p_eLongHitState[161] = -1;
      p_eLongHitState[162] = -1;
      p_eLongHitState[163] = -1;
      p_eLongHitState[165] = 90;
      p_eLongHitState[166] = 124;
      p_eLongHitState[167] = 125;
      p_eLongHitState[168] = 126;
      p_eLongHitState[169] = 74;
      p_eLongHitState[170] = 75;
      p_eLongHitState[171] = 76;
      p_eLongHitState[172] = 139;
      p_eLongHitState[173] = 140;
      p_eLongHitState[174] = 141;
      p_eLongHitState[175] = -1;
      p_eLongHitState[176] = -1;
      p_eLongHitState[177] = -1;
      p_eLongHitState[178] = -1;
      p_eLongHitState[180] = 91;
      p_eLongHitState[181] = 115;
      p_eLongHitState[182] = 116;
      p_eLongHitState[183] = 117;
      p_eLongHitState[184] = 71;
      p_eLongHitState[185] = 72;
      p_eLongHitState[186] = 73;
      p_eLongHitState[187] = 130;
      p_eLongHitState[188] = 131;
      p_eLongHitState[189] = 132;
      p_eLongHitState[190] = -1;
      p_eLongHitState[191] = -1;
      p_eLongHitState[192] = -1;
      p_eLongHitState[193] = -1;
      p_eLongHitState[195] = 91;
      p_eLongHitState[196] = 115;
      p_eLongHitState[197] = 116;
      p_eLongHitState[198] = 117;
      p_eLongHitState[199] = 74;
      p_eLongHitState[200] = 75;
      p_eLongHitState[201] = 76;
      p_eLongHitState[202] = 130;
      p_eLongHitState[203] = 131;
      p_eLongHitState[204] = 132;
      p_eLongHitState[205] = -1;
      p_eLongHitState[206] = -1;
      p_eLongHitState[207] = -1;
      p_eLongHitState[208] = -1;
      p_eLongHitState[210] = 91;
      p_eLongHitState[211] = 115;
      p_eLongHitState[212] = 116;
      p_eLongHitState[213] = 117;
      p_eLongHitState[214] = 68;
      p_eLongHitState[215] = 69;
      p_eLongHitState[216] = 70;
      p_eLongHitState[217] = 130;
      p_eLongHitState[218] = 131;
      p_eLongHitState[219] = 132;
      p_eLongHitState[220] = -1;
      p_eLongHitState[221] = -1;
      p_eLongHitState[222] = -1;
      p_eLongHitState[223] = -1;
      p_eLongHitState[225] = 91;
      p_eLongHitState[226] = 115;
      p_eLongHitState[227] = 116;
      p_eLongHitState[228] = 117;
      p_eLongHitState[229] = 79;
      p_eLongHitState[230] = 79;
      p_eLongHitState[231] = 79;
      p_eLongHitState[232] = 130;
      p_eLongHitState[233] = 131;
      p_eLongHitState[234] = 132;
      p_eLongHitState[235] = 91;
      p_eLongHitState[236] = 115;
      p_eLongHitState[237] = 116;
      p_eLongHitState[238] = 117;
      p_eLongHitState[240] = 91;
      p_eLongHitState[241] = 115;
      p_eLongHitState[242] = 116;
      p_eLongHitState[243] = 117;
      p_eLongHitState[244] = 65;
      p_eLongHitState[245] = 66;
      p_eLongHitState[246] = 67;
      p_eLongHitState[247] = 130;
      p_eLongHitState[248] = 131;
      p_eLongHitState[249] = 132;
      p_eLongHitState[250] = -1;
      p_eLongHitState[251] = -1;
      p_eLongHitState[252] = -1;
      p_eLongHitState[253] = -1;
    }
    p_eLongHitState += 255;
    ++p_ptPrev;
    v8 += 17;
  }
  while ( (int)p_eLongHitState < 139179948 );
}

// source: j/0/human/soldiertypes/humansoldier.c:989  [anchor-mhash]
void __cdecl HumanSoldier_HandleActivation(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct GetActivateContext_t tGetActivateContext; };
    struct { char igi2_o1[4]; struct ActivateContext_t tActivateContext; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QReference_s *v2; // eax
  struct QTask_s *pxObject; // ebp
  struct QReference_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct GetActivateContext_t *); // eax
  void (__cdecl *v6)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v7; // ecx
  struct QTask_s *ptPrev; // eax
  void (__cdecl *v9)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *ptTail; // ecx
  struct LevelFlow_s *v11; // eax
  int eQTaskType; // edx
  void (__cdecl *v13)(struct QTask_s *, struct ActivateContext_t *); // eax

  ptHead = ptQTask[75].tQTaskRefList.ptHead;
  if ( (unsigned int)ptHead >= 0x1000 )
    return;
  v2 = Level_atLevelQTaskID[(_DWORD)ptHead];
  if ( !v2 )
    return;
  pxObject = (struct QTask_s *)v2->pxObject;
  if ( !pxObject )
    return;
  v4 = ptQTask[46].tQTaskRefList.ptHead;
  if ( v4 )
  {
    QReference_Delete(v4, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  ptQTask[46].tQTaskRefList.ptHead = QTask_NewQTaskRef(pxObject);
  igi2_frame.tGetActivateContext.eHumanActivate = 0;
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct GetActivateContext_t *))QTask_aatQTaskFinalEvent[GameFunctions_eGetActivateQTaskEvent][pxObject->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(pxObject, &igi2_frame.tGetActivateContext);
  switch ( igi2_frame.tGetActivateContext.eHumanActivate )
  {
    case 1:
      v11 = LevelFlow_ptLevelFlow;
      LOBYTE(pxObject[14].tQTaskRefList.ptMiddle) = 1;
      pxObject[14].tQTaskRefList.ptTail = (struct QReference_s *)v11->nTick;
      pxObject[17].tQTaskChildren.ptHead = nullptr;
      break;
    case 2:
      BYTE2(pxObject[23].tQTaskRefList.ptHead) ^= 1u;
      BYTE1(pxObject[23].tQTaskRefList.ptHead) = 1;
      v9 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
           + (int)ptQTask[31].ptPrev);
      if ( v9 )
        v9(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      ptTail = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)86;
      ptPrev = (struct QTask_s *)ptTail[28].pxObject;
      goto LABEL_17;
    case 5:
      v6 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
           + (int)ptQTask[31].ptPrev);
      if ( v6 )
        v6(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      v7 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)85;
      ptPrev = (struct QTask_s *)v7[28].ptPrev;
LABEL_17:
      ptQTask[31].tQTaskChildren.ptHead = ptPrev;
      ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptPrev)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      break;
  }
  igi2_frame.tActivateContext.ptHumanQTask = ptQTask;
  qmemcpy(&igi2_frame.tActivateContext.tPos, &ptQTask[1], sizeof(igi2_frame.tActivateContext.tPos));
  igi2_frame.tActivateContext.pvChannel = (float *)&ptQTask[19].ptPrev;
  eQTaskType = pxObject->eQTaskType;
  igi2_frame.tActivateContext.pvLastChannel = (float *)&ptQTask[12].ptParent;
  v13 = (void (__cdecl *)(struct QTask_s *, struct ActivateContext_t *))QTask_aatQTaskFinalEvent[GameFunctions_eActivateQTaskEvent][eQTaskType].pfHandler;
  igi2_frame.tActivateContext.nActivateTime = 0;
  if ( v13 )
    v13(pxObject, &igi2_frame.tActivateContext);
  ++*(int *)&ptQTask[46].tQTaskRefList.ptTail;
}

// source: j/0/human/soldiertypes/humansoldier.c:1087  [size]
void __cdecl HumanSoldier_UpdateFeetSound(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/human/soldiertypes/humansoldier.c:1102  [anchor-mhash]
void __cdecl HumanSoldier_FireUpperBodySignalHandler(struct QTask_s *ptQTask)
{
  struct Weapon_s *v2; // ecx
  struct WeaponTypeItem_s *ptActiveWeapon; // eax
  unsigned int v4; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // eax
  struct WeaponGetFireTypeAmmoContext_s tAmmoContext; // [esp+Ch] [ebp-14h] BYREF
  unsigned int ptQTaska = *(unsigned int *)&ptQTask; // [esp+24h] [ebp+4h] ARGSLOT

  ptQTaska = *(_DWORD *)&ptQTask[30].eQTaskType;
  if ( ptQTask[34].tQTaskRefList.ptHead
    && (v2 = (struct Weapon_s *)ptQTask[33].ptNext) != nullptr
    && *(_DWORD *)&ptQTask[32].eQTaskType != 2
    && !ptQTask[76].tQTaskChildren.ptHead
    && (ptActiveWeapon = v2->tPrivate.ptActiveWeapon) != nullptr
    && ptActiveWeapon->ptWeaponType
    && ((int)ptQTask[74].ptParent & 1) == 0 )
  {
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(v2, v2->tPrivate.ptActiveWeapon, 0, &tAmmoContext);
    v4 = ptQTaska;
    if ( (ptQTaska & 0x20000) != 0 )
    {
      ptNext = ptQTask[33].ptNext;
LABEL_23:
      ptNext[2].ptParent = (struct QTask_s *)1;
      ptNext[1].tQTaskChildren.ptTail = nullptr;
      goto LABEL_24;
    }
    if ( (ptQTaska & 0x10000) != 0 )
    {
      v6 = ptQTask[33].ptNext;
      v6[2].ptParent = (struct QTask_s *)1;
      v6[1].tQTaskChildren.ptTail = nullptr;
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_HitUpperBodySignalHandler;
      return;
    }
    if ( (ptQTaska & 0x10) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 10, 0, 0.0);
      v4 = ptQTaska;
    }
    if ( (v4 & 0x200) != 0 )
    {
      Weapon_Fire(ptQTask[33].ptNext, 0);
      return;
    }
    v7 = ptQTask[33].ptNext;
    v7[2].ptParent = (struct QTask_s *)1;
    v7[1].tQTaskChildren.ptTail = nullptr;
    if ( (v4 & 0x1000000) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 15, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_AimUpperBodySignalHandler;
      return;
    }
    if ( (v4 & 0x800) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 11, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_ReloadUpperBodySignalHandler;
      return;
    }
    if ( (v4 & 0x800000) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 102, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_TenseUpperBodySignalHandler;
      return;
    }
  }
  else
  {
    ptNext = ptQTask[33].ptNext;
    if ( ptNext )
      goto LABEL_23;
  }
LABEL_24:
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
}

// source: j/0/human/soldiertypes/humansoldier.c:1207  [anchor-mhash]
void __cdecl HumanSoldier_AimUpperBodySignalHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct Game_s *v2; // eax
  unsigned int v3; // ebx
  unsigned int v4; // ecx
  unsigned int v5; // edx
  int v6; // ebx
  unsigned int v7; // edx
  char azChangeSound[4][32]; // [esp+8h] [ebp-80h] BYREF

  v1 = *(_DWORD *)&ptQTask[30].eQTaskType;
  if ( !ptQTask[34].tQTaskRefList.ptHead
    || (v1 & 0x30000) != 0
    || *(_DWORD *)&ptQTask[32].eQTaskType == 2
    || (v1 & 0x1800000) == 0
    || ptQTask[76].tQTaskChildren.ptHead
    || ((int)ptQTask[74].ptParent & 1) != 0 )
  {
    strcpy(azChangeSound[0], "changeweapon_01");
    *(_QWORD *)&azChangeSound[0][16] = 0;
    *(_QWORD *)&azChangeSound[0][24] = 0;
    strcpy(azChangeSound[1], "changeweapon_02");
    *(_QWORD *)&azChangeSound[1][16] = 0;
    strcpy(azChangeSound[2], "changeweapon_03");
    *(_QWORD *)&azChangeSound[1][24] = 0;
    *(_QWORD *)&azChangeSound[2][16] = 0;
    strcpy(azChangeSound[3], "changeweapon_04");
    *(_QWORD *)&azChangeSound[2][24] = 0;
    v2 = Game_ptGame;
    *(_QWORD *)&azChangeSound[3][16] = 0;
    *(_QWORD *)&azChangeSound[3][24] = 0;
    v3 = Game_ptGame->tRunRandomState.anRandom[1];
    v4 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
    v5 = Game_ptGame->tRunRandomState.anRandom[0];
    Game_ptGame->tRunRandomState.anRandom[2] = v4;
    v6 = v4 ^ v3;
    v2->tRunRandomState.anRandom[1] = v6;
    v7 = v6 + v5;
    v2->tRunRandomState.anRandom[0] = v7;
    SoundSys_NewSoundFn(ptQTask, azChangeSound[v7 & 3]);
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 1.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
  }
  else if ( (v1 & 0x10000) != 0 )
  {
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_HitUpperBodySignalHandler;
  }
  else if ( (v1 & 0x200) != 0 )
  {
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 10, 0, 0.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_FireUpperBodySignalHandler;
  }
  else if ( (v1 & 0x800) != 0 )
  {
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 11, 0, 0.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_ReloadUpperBodySignalHandler;
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:1277  [anchor-mhash]
void __cdecl HumanSoldier_ReloadUpperBodySignalHandler(struct QTask_s *ptQTask)
{
  int v1; // ebx
  struct QTask_s *v2; // eax
  struct QTask_s *ptNext; // eax

  v1 = *(_DWORD *)&ptQTask[30].eQTaskType;
  if ( !ptQTask[34].tQTaskRefList.ptHead
    || (v1 & 0x30000) != 0
    || *(_DWORD *)&ptQTask[32].eQTaskType == 2
    || ptQTask[76].tQTaskChildren.ptHead
    || ((int)ptQTask[74].ptParent & 1) != 0 )
  {
LABEL_19:
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
    return;
  }
  if ( (v1 & 0x10000) == 0 )
  {
    if ( (v1 & 0x10) == 0 )
      return;
    ptNext = ptQTask[33].ptNext;
    if ( ptNext )
      Weapon_Reload(ptNext);
    if ( (v1 & 0x200) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 10, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_FireUpperBodySignalHandler;
      return;
    }
    if ( (v1 & 0x1000000) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 15, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_AimUpperBodySignalHandler;
      return;
    }
    if ( (v1 & 0x800000) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 102, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_TenseUpperBodySignalHandler;
      return;
    }
    goto LABEL_19;
  }
  v2 = ptQTask[33].ptNext;
  if ( v2 )
    Weapon_Reload(v2);
  ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_HitUpperBodySignalHandler;
}

// source: j/0/human/soldiertypes/humansoldier.c:1366  [anchor-mhash]
void __cdecl HumanSoldier_TenseUpperBodySignalHandler(struct QTask_s *ptQTask)
{
  int v1; // eax

  v1 = *(_DWORD *)&ptQTask[30].eQTaskType;
  if ( (v1 & 0x20000) != 0
    || !ptQTask[34].tQTaskRefList.ptHead
    || (v1 & 0x800000) == 0
    || *(_DWORD *)&ptQTask[32].eQTaskType == 2
    || ptQTask[76].tQTaskChildren.ptHead
    || ((int)ptQTask[74].ptParent & 1) != 0 )
  {
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
  }
  else if ( (v1 & 0x10000) != 0 )
  {
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_HitUpperBodySignalHandler;
  }
  else if ( (v1 & 0x200) != 0 )
  {
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 10, 0, 0.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_FireUpperBodySignalHandler;
  }
  else if ( (v1 & 0x1000000) != 0 )
  {
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 15, 0, 0.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_AimUpperBodySignalHandler;
  }
  else if ( (v1 & 0x800) != 0 )
  {
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 11, 0, 0.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_ReloadUpperBodySignalHandler;
  }
  else if ( (v1 & 0x10) != 0 )
  {
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 102, 0, 0.0);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:1454  [anchor-mhash]
void __cdecl HumanSoldier_HitUpperBodySignalHandler(struct QTask_s *ptQTask)
{
  int v1; // eax

  v1 = *(_DWORD *)&ptQTask[30].eQTaskType;
  if ( !ptQTask[34].tQTaskRefList.ptHead
    || ptQTask[76].tQTaskChildren.ptHead
    || ((int)ptQTask[74].ptParent & 1) != 0
    || (v1 & 1) != 0 )
  {
    if ( ((int)ptQTask[74].ptParent & 1) != 0 )
      goto LABEL_12;
    if ( (v1 & 0x200) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 10, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_FireUpperBodySignalHandler;
      return;
    }
    if ( (v1 & 0x1000000) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 15, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_AimUpperBodySignalHandler;
      return;
    }
    if ( (v1 & 0x800) == 0 )
    {
LABEL_12:
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
    }
    else
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 11, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_ReloadUpperBodySignalHandler;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:1538  [anchor-mhash]
void __cdecl HumanSoldier_RaiseWeaponUpperBodySignalHandler(struct QTask_s *ptQTask)
{
  int v1; // eax

  v1 = *(_DWORD *)&ptQTask[30].eQTaskType;
  if ( ((int)ptQTask[74].ptParent & 1) != 0
    || ptQTask[76].tQTaskChildren.ptHead
    || *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  }
  else if ( (v1 & 0x10) != 0 )
  {
    if ( (v1 & 0x800) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 11, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_ReloadUpperBodySignalHandler;
    }
    else if ( (v1 & 0x200) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 10, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_FireUpperBodySignalHandler;
    }
    else if ( (v1 & 0x1000000) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 15, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_AimUpperBodySignalHandler;
    }
    else if ( (v1 & 0x800000) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 102, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_TenseUpperBodySignalHandler;
    }
    else
    {
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:1612  [anchor-caller]
void __cdecl HumanSoldier_IdleUpperBodySignalHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v5; };
    struct { char igi2_o1[16]; float vBlendTime; };
    struct { char igi2_o2[20]; char azChangeSound[4][32]; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  struct QTask_s *ptParent; // ebx
  unsigned int RandomNumberBelowLimit; // eax
  struct QReference_s *ptHead; // eax

  v1 = *(_DWORD *)&ptQTask[30].eQTaskType;
  ptParent = ptQTask[48].ptParent;
  if ( ((int)ptQTask[74].ptParent & 1) != 0
    || ptQTask[76].tQTaskChildren.ptHead
    || *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  }
  else if ( ptQTask[31].ptPrev != (struct QTask_s *)85 && HumanAnim_IsBlendFinished(ptQTask) )
  {
    if ( (v1 & 0x10000) != 0 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_HitUpperBodySignalHandler;
    }
    else if ( (v1 & 0x800) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 11, 0, 0.0);
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_ReloadUpperBodySignalHandler;
    }
    else if ( (v1 & 0x1800000) != 0 )
    {
      *(_QWORD *)&igi2_frame.azChangeSound[0][20] = 0;
      strcpy(igi2_frame.azChangeSound[0], "changeweapon_01");
      strcpy(igi2_frame.azChangeSound[1], "changeweapon_02");
      *(_DWORD *)&igi2_frame.azChangeSound[0][16] = 0;
      *(_DWORD *)&igi2_frame.azChangeSound[0][28] = 0;
      strcpy(igi2_frame.azChangeSound[2], "changeweapon_03");
      *(_QWORD *)&igi2_frame.azChangeSound[1][16] = 0;
      *(_DWORD *)&igi2_frame.azChangeSound[2][16] = 0;
      *(_QWORD *)&igi2_frame.azChangeSound[1][24] = 0;
      *(_QWORD *)&igi2_frame.azChangeSound[2][20] = 0;
      *(_DWORD *)&igi2_frame.azChangeSound[2][28] = 0;
      *(_QWORD *)&igi2_frame.azChangeSound[3][20] = 0;
      strcpy(igi2_frame.azChangeSound[3], "changeweapon_04");
      *(_DWORD *)&igi2_frame.azChangeSound[3][16] = 0;
      *(_DWORD *)&igi2_frame.azChangeSound[3][28] = 0;
      RandomNumberBelowLimit = Random_GetRandomNumberBelowLimit(&Game_ptGame->tRunRandomState, 4);
      SoundSys_NewSoundFn(ptQTask, igi2_frame.azChangeSound[RandomNumberBelowLimit]);
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 16, 0, 0.0);
      ptHead = ptQTask[34].tQTaskRefList.ptHead;
      ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_RaiseWeaponUpperBodySignalHandler;
      if ( ptHead )
      {
        igi2_frame.v5 = (double)(int)ptHead[6].ptNext[1].ptPrev * 0.00020833333837799728
           + (double)(int)ptHead[6].ptNext[1].ptPrev * 0.00020833333837799728;
        HumanAnim_ScaleAnimationTimeStep(ptQTask, igi2_frame.v5);
      }
    }
    else if ( !ptQTask[34].tQTaskRefList.ptHead )
    {
      igi2_frame.vBlendTime = 0.0;
      if ( ptParent )
      {
        if ( HIBYTE(ptParent[111].tQTaskChildren.ptMiddle) )
          igi2_frame.vBlendTime = 1.0;
      }
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 0, 0, igi2_frame.vBlendTime);
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:1715  [size]
struct QTask_s *__cdecl HumanSoldier_MaintainUpperBodyState(struct QTask_s *ptQTask)
{
  return (struct QTask_s *)((int (__cdecl *)(struct QTask_s *))ptQTask[74].tQTaskRefList.ptTail)(ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:1742  [size]
void __cdecl HumanSoldier_Update(struct QTask_s *ptQTask)
{
  State_Run((struct State_s *)&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  if ( *(float *)&ptQTask[21].tQTaskChildren.ptTail != 0.0 )
    LOBYTE(ptQTask[75].ptPrev) ^= 1u;
  ((void (__cdecl *)(struct QTask_s *))ptQTask[74].tQTaskRefList.ptTail)(ptQTask);
  *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x10000u;
  Human_UpdateBody(ptQTask);
  HumanView_UpdateView(ptQTask[33].tQTaskChildren.ptTail, ptQTask);
  AnimController_Step(
    (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
    (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
  if ( ptQTask[44].tQTaskRefList.ptTail )
    Human_Attach(ptQTask);
  else
    Human_Move(ptQTask);
  HumanView_UpdateBody(ptQTask[33].tQTaskChildren.ptTail, ptQTask, true);
  Weapon_UpdateStatus(ptQTask[33].ptNext);
  Human_Notify(ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:1896  [anchor-mhash]
void __cdecl HumanSoldier_StateSignalHandler(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct State_s *v2; // esi
  unsigned int v3; // ebp
  struct QReference_s *ptHead; // eax
  unsigned int v5; // ebp
  struct WeaponType_s *WeaponTypeFromID; // eax

  v2 = ptState;
  v3 = ptState->bSignal & 0x1803C00E;
  if ( *(float *)&ptQTask[22].tQTaskRefList.ptTail != 0.0 )
    v3 |= 0x40000000u;
  if ( *(float *)&ptQTask[22].ptParent != 0.0 )
    v3 |= 0x80000000;
  if ( ((int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev & 4) != 0 )
    v3 |= 1u;
  ptHead = ptQTask[34].tQTaskRefList.ptHead;
  if ( ptHead && ((int)ptHead[3].pxObject & 4) != 0 )
    v3 |= 0x10u;
  if ( LOBYTE(ptQTask[75].ptPrev) )
    v5 = v3 | 0x40000;
  else
    v5 = v3 & 0xFFFBFFFF;
  if ( *(float *)&ptQTask[19].tQTaskChildren.ptMiddle != 0.0 )
    v5 |= 0x20u;
  if ( *(float *)&ptQTask[19].tQTaskChildren.ptTail != 0.0 )
    v5 |= 0x40u;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptHead != 0.0 )
    v5 |= 0x80u;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptMiddle != 0.0 )
    v5 |= 0x100u;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptTail != 0.0 )
    v5 |= 0x200u;
  if ( *(float *)&ptQTask[19].ptParent != 0.0 )
    v5 |= 0x400u;
  if ( *(float *)&ptQTask[19].eQTaskType != 0.0 )
    v5 |= 0x800u;
  if ( *(float *)&ptQTask[20].ptNext != 0.0 )
    v5 |= 0x1000u;
  if ( *(float *)&ptQTask[22].tQTaskRefList.ptHead != 0.0 )
    v5 |= 0x20000000u;
  if ( *(float *)&ptQTask[21].tQTaskRefList.ptHead != 0.0 )
    v5 |= 0x2000u;
  if ( *(float *)&ptQTask[21].tQTaskRefList.ptMiddle != 0.0 )
    v5 |= 0x100000u;
  if ( *(float *)&ptQTask[21].tQTaskRefList.ptTail != 0.0 )
    v5 |= 0x200000u;
  if ( *(float *)&ptQTask[21].ptParent != 0.0 )
  {
    v5 |= 0x400000u;
    if ( ptQTask[31].ptPrev != (struct QTask_s *)85 )
    {
      ptQTask[75].tQTaskRefList.ptHead = (struct QReference_s *)(__int64)*(float *)&ptQTask[21].ptParent;
      HumanSoldier_HandleActivation(ptQTask);
      ptQTask[21].ptParent = nullptr;
    }
  }
  if ( *(float *)&ptQTask[22].ptNext != 0.0 )
    v5 |= 0x800000u;
  if ( *(float *)&ptQTask[22].ptPrev != 0.0 )
    v5 |= 0x1000000u;
  if ( *(float *)&ptQTask[22].tQTaskChildren.ptHead != 0.0 )
  {
    if ( ptQTask[33].ptNext )
    {
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((__int64)*(float *)&ptQTask[22].tQTaskChildren.ptHead);
      if ( WeaponTypeFromID )
      {
        Weapon_Activate(ptQTask[33].ptNext, WeaponTypeFromID->zWeaponScriptID, false);
        v2 = ptState;
      }
    }
  }
  if ( *(float *)&ptQTask[22].tQTaskChildren.ptMiddle != 0.0 )
    v5 |= 0x2000000u;
  if ( *(float *)&ptQTask[22].tQTaskChildren.ptTail != 0.0 )
    v5 |= 0x4000000u;
  if ( *(float *)&ptQTask[22].tQTaskRefList.ptMiddle != 0.0 )
    v5 |= 0x80000u;
  v2->bSignal = v5;
}

// source: j/0/human/soldiertypes/humansoldier.c:2081  [anchor-mhash]
void __cdecl HumanSoldier_InitStateStand(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *v4; // esi
  float ptQTaska = *(float *)&ptQTask; // [esp+1Ch] [ebp+8h] ARGSLOT

  ptParent = ptQTask[74].ptParent;
  v4 = ptQTask[48].ptParent;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 0;
  if ( ((unsigned __int8)ptParent & 1) != 0 )
  {
    ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  }
  if ( (ptState->bSignal & 0x800000) != 0 )
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 103, 0, 0.0);
    ptState->pfState = HumanSoldier_RunStateStandTense;
  }
  else
  {
    ptQTaska = 0.0;
    if ( v4 && HIBYTE(v4[111].tQTaskChildren.ptMiddle) )
      ptQTaska = 0.5;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 0, 0, ptQTaska);
    ptState->pfState = HumanSoldier_RunStateStand;
  }
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:2121  [anchor-mhash]
void __cdecl HumanSoldier_RunStateStand(struct State_s *ptState, struct QTask_s *ptQTask)
{
  signed int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v7)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v42)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v43)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v44)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v45)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v46)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v47)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v48)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v49)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v50)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v51)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v52)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v53)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v54)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v55)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v56)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) == 0 )
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = apfState[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x10000) != 0 )
  {
    v6 = ptState->apfExitState[ptState->nState];
    if ( v6 )
      v6(ptState, ptQTask);
    v7 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 41;
    v8 = v7[41];
    ptState->pfState = v8;
    v8(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x20000) != 0 )
  {
    v9 = ptState->apfExitState[ptState->nState];
    if ( v9 )
      v9(ptState, ptQTask);
    v10 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 71;
    v11 = v10[71];
    ptState->pfState = v11;
    v11(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x2008) != 0 )
  {
    v12 = ptState->apfExitState[ptState->nState];
    if ( v12 )
      v12(ptState, ptQTask);
    v13 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 19;
    v14 = v13[19];
    ptState->pfState = v14;
    v14(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x100000) != 0 )
  {
    v15 = ptState->apfExitState[ptState->nState];
    if ( v15 )
      v15(ptState, ptQTask);
    v16 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v17 = v16[21];
    ptState->pfState = v17;
    v17(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x2000000) != 0 )
  {
    v18 = ptState->apfExitState[ptState->nState];
    if ( v18 )
      v18(ptState, ptQTask);
    v19 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 12;
    v20 = v19[12];
    ptState->pfState = v20;
    v20(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x200000) != 0 )
  {
    v21 = ptState->apfExitState[ptState->nState];
    if ( v21 )
      v21(ptState, ptQTask);
    v22 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 84;
    v23 = v22[84];
    ptState->pfState = v23;
    v23(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x4000000) != 0 )
  {
    v24 = ptState->apfExitState[ptState->nState];
    if ( v24 )
      v24(ptState, ptQTask);
    v25 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 14;
    v26 = v25[14];
    ptState->pfState = v26;
    v26(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x20000000) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, ptQTask);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 1;
    v29 = v28[1];
    ptState->pfState = v29;
    v29(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x80000) != 0 )
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, ptQTask);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 100;
    v32 = v31[100];
    ptState->pfState = v32;
    v32(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x20) != 0 )
  {
    v33 = ptState->apfExitState[ptState->nState];
    if ( v33 )
      v33(ptState, ptQTask);
    v34 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 24;
    v35 = v34[24];
    ptState->pfState = v35;
    v35(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x40) != 0 )
  {
    v36 = ptState->apfExitState[ptState->nState];
    if ( v36 )
      v36(ptState, ptQTask);
    v37 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 25;
    v38 = v37[25];
    ptState->pfState = v38;
    v38(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x100) != 0 )
  {
    v39 = ptState->apfExitState[ptState->nState];
    if ( v39 )
      v39(ptState, ptQTask);
    v40 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 26;
    v41 = v40[26];
    ptState->pfState = v41;
    v41(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x800000) != 0 && (bSignal & 0x80u) != 0 )
  {
    v42 = ptState->apfExitState[ptState->nState];
    if ( v42 )
      v42(ptState, ptQTask);
    v43 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v44 = v43[23];
    ptState->pfState = v44;
    v44(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x40000) != 0 )
  {
    if ( (bSignal & 0x80u) != 0 )
    {
      v45 = ptState->apfExitState[ptState->nState];
      if ( v45 )
        v45(ptState, ptQTask);
      v46 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 6;
      v47 = v46[6];
      ptState->pfState = v47;
      v47(ptState, ptQTask);
      return;
    }
    goto LABEL_67;
  }
  if ( (bSignal & 0x80u) == 0 )
  {
LABEL_67:
    if ( (bSignal & 0x40000000) != 0 )
    {
      v51 = ptState->apfExitState[ptState->nState];
      if ( v51 )
        v51(ptState, ptQTask);
      v52 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 8;
      v53 = v52[8];
      ptState->pfState = v53;
      v53(ptState, ptQTask);
    }
    else if ( bSignal < 0 )
    {
      v54 = ptState->apfExitState[ptState->nState];
      if ( v54 )
        v54(ptState, ptQTask);
      v55 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 9;
      v56 = v55[9];
      ptState->pfState = v56;
      v56(ptState, ptQTask);
    }
    return;
  }
  v48 = ptState->apfExitState[ptState->nState];
  if ( v48 )
    v48(ptState, ptQTask);
  v49 = ptState->apfState;
  ptState->nPreviousState = ptState->nState;
  ptState->nState = 5;
  v50 = v49[5];
  ptState->pfState = v50;
  v50(ptState, ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:2179  [anchor-mhash]
void __cdecl HumanSoldier_InitStateStandTurn(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.5);
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  ptState->pfState = HumanSoldier_RunStateStandTurn;
}

// source: j/0/human/soldiertypes/humansoldier.c:2201  [anchor-mhash]
void __cdecl HumanSoldier_RunStateStandTurn(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v7)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v42)(struct State_s *, struct QTask_s *); // eax
  int nState; // ecx
  void (__cdecl **v44)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v45)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) == 0 )
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = apfState[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x10000) != 0 )
  {
    v6 = ptState->apfExitState[ptState->nState];
    if ( v6 )
      v6(ptState, ptQTask);
    v7 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 41;
    v8 = v7[41];
    ptState->pfState = v8;
    v8(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x20000) != 0 )
  {
    v9 = ptState->apfExitState[ptState->nState];
    if ( v9 )
      v9(ptState, ptQTask);
    v10 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 71;
    v11 = v10[71];
    ptState->pfState = v11;
    v11(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x2008) != 0 )
  {
    v12 = ptState->apfExitState[ptState->nState];
    if ( v12 )
      v12(ptState, ptQTask);
    v13 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 19;
    v14 = v13[19];
    ptState->pfState = v14;
    v14(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x100000) != 0 )
  {
    v15 = ptState->apfExitState[ptState->nState];
    if ( v15 )
      v15(ptState, ptQTask);
    v16 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v17 = v16[21];
    ptState->pfState = v17;
    v17(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x2000000) != 0 )
  {
    v18 = ptState->apfExitState[ptState->nState];
    if ( v18 )
      v18(ptState, ptQTask);
    v19 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 12;
    v20 = v19[12];
    ptState->pfState = v20;
    v20(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x200000) != 0 )
  {
    v21 = ptState->apfExitState[ptState->nState];
    if ( v21 )
      v21(ptState, ptQTask);
    v22 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 84;
    v23 = v22[84];
    ptState->pfState = v23;
    v23(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x4000000) != 0 )
  {
    v24 = ptState->apfExitState[ptState->nState];
    if ( v24 )
      v24(ptState, ptQTask);
    v25 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 14;
    v26 = v25[14];
    ptState->pfState = v26;
    v26(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x800000) != 0 )
  {
LABEL_56:
    v42 = ptState->apfExitState[ptState->nState];
    if ( v42 )
      v42(ptState, ptQTask);
    nState = ptState->nState;
    v44 = ptState->apfState;
    ptState->nState = 0;
    ptState->nPreviousState = nState;
    v45 = *v44;
    ptState->pfState = *v44;
    v45(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x40000) != 0 )
  {
    if ( (bSignal & 0x80u) != 0 )
    {
      v27 = ptState->apfExitState[ptState->nState];
      if ( v27 )
        v27(ptState, ptQTask);
      v28 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 6;
      v29 = v28[6];
      ptState->pfState = v29;
      v29(ptState, ptQTask);
      return;
    }
    goto LABEL_43;
  }
  if ( (bSignal & 0x80u) == 0 )
  {
LABEL_43:
    if ( (bSignal & 0x20) != 0 )
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, ptQTask);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 24;
      v35 = v34[24];
      ptState->pfState = v35;
      v35(ptState, ptQTask);
      return;
    }
    if ( (bSignal & 0x40) != 0 )
    {
      v36 = ptState->apfExitState[ptState->nState];
      if ( v36 )
        v36(ptState, ptQTask);
      v37 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 25;
      v38 = v37[25];
      ptState->pfState = v38;
      v38(ptState, ptQTask);
      return;
    }
    if ( (bSignal & 0x100) != 0 )
    {
      v39 = ptState->apfExitState[ptState->nState];
      if ( v39 )
        v39(ptState, ptQTask);
      v40 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 26;
      v41 = v40[26];
      ptState->pfState = v41;
      v41(ptState, ptQTask);
      return;
    }
    if ( (bSignal & 0x20000000) != 0 )
      return;
    goto LABEL_56;
  }
  v30 = ptState->apfExitState[ptState->nState];
  if ( v30 )
    v30(ptState, ptQTask);
  v31 = ptState->apfState;
  ptState->nPreviousState = ptState->nState;
  ptState->nState = 5;
  v32 = v31[5];
  ptState->pfState = v32;
  v32(ptState, ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:2249  [anchor-mhash]
void __cdecl HumanSoldier_RunStateStandTense(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v42)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v43)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v44)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 71;
      v11 = v10[71];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2008) != 0 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 19;
      v14 = v13[19];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 21;
      v17 = v16[21];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2000000) != 0 )
    {
      v18 = ptState->apfExitState[ptState->nState];
      if ( v18 )
        v18(ptState, ptQTask);
      v19 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 12;
      v20 = v19[12];
      ptState->pfState = v20;
      v20(ptState, ptQTask);
    }
    else if ( (bSignal & 0x200000) != 0 )
    {
      v21 = ptState->apfExitState[ptState->nState];
      if ( v21 )
        v21(ptState, ptQTask);
      v22 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 84;
      v23 = v22[84];
      ptState->pfState = v23;
      v23(ptState, ptQTask);
    }
    else if ( (bSignal & 0x4000000) != 0 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, ptQTask);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 14;
      v26 = v25[14];
      ptState->pfState = v26;
      v26(ptState, ptQTask);
    }
    else if ( (bSignal & 0x80000) != 0 )
    {
      v27 = ptState->apfExitState[ptState->nState];
      if ( v27 )
        v27(ptState, ptQTask);
      v28 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 100;
      v29 = v28[100];
      ptState->pfState = v29;
      v29(ptState, ptQTask);
    }
    else if ( (bSignal & 0x800000) != 0 )
    {
      if ( (bSignal & 0x80u) == 0 )
      {
        if ( (bSignal & 0x20) != 0 )
        {
          v33 = ptState->apfExitState[ptState->nState];
          if ( v33 )
            v33(ptState, ptQTask);
          v34 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 24;
          v35 = v34[24];
          ptState->pfState = v35;
          v35(ptState, ptQTask);
        }
        else if ( (bSignal & 0x40) != 0 )
        {
          v36 = ptState->apfExitState[ptState->nState];
          if ( v36 )
            v36(ptState, ptQTask);
          v37 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 25;
          v38 = v37[25];
          ptState->pfState = v38;
          v38(ptState, ptQTask);
        }
        else if ( (bSignal & 0x100) != 0 )
        {
          v39 = ptState->apfExitState[ptState->nState];
          if ( v39 )
            v39(ptState, ptQTask);
          v40 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 26;
          v41 = v40[26];
          ptState->pfState = v41;
          v41(ptState, ptQTask);
        }
      }
      else
      {
        v30 = ptState->apfExitState[ptState->nState];
        if ( v30 )
          v30(ptState, ptQTask);
        v31 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 23;
        v32 = v31[23];
        ptState->pfState = v32;
        v32(ptState, ptQTask);
      }
    }
    else
    {
      v42 = ptState->apfExitState[ptState->nState];
      if ( v42 )
        v42(ptState, ptQTask);
      v43 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v44 = *v43;
      ptState->pfState = *v43;
      v44(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:2311  [size]
void __cdecl HumanSoldier_InitStatePanicForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStatePanicForward;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2331  [anchor-mhash]
void __cdecl HumanSoldier_RunStatePanicForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax

  Human_MoveOnGround(ptQTask, 458.75201416015625, 0.0);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 71;
      v11 = v10[71];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2000) != 0 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 19;
      v14 = v13[19];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 21;
      v17 = v16[21];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2000000) != 0 )
    {
      v18 = ptState->apfExitState[ptState->nState];
      if ( v18 )
        v18(ptState, ptQTask);
      v19 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 12;
      v20 = v19[12];
      ptState->pfState = v20;
      v20(ptState, ptQTask);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v21 = ptState->apfExitState[ptState->nState];
      if ( v21 )
        v21(ptState, ptQTask);
      v22 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 6;
      v23 = v22[6];
      ptState->pfState = v23;
      v23(ptState, ptQTask);
    }
    else
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, ptQTask);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 5;
      v26 = v25[5];
      ptState->pfState = v26;
      v26(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:2367  [size]
void __cdecl HumanSoldier_InitStateTenseRunForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateTenseRunForward;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2387  [anchor-mhash]
void __cdecl HumanSoldier_RunStateTenseRunForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  float v36; // [esp+0h] [ebp-10h]

  v36 = *(float *)&ptQTask[75].tQTaskChildren.ptTail * 458.75201416015625;
  Human_MoveOnGround(ptQTask, v36, 0.0);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 71;
      v11 = v10[71];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2000) != 0 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 19;
      v14 = v13[19];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 21;
      v17 = v16[21];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
    else if ( (bSignal & 0x80000) != 0 )
    {
      v18 = ptState->apfExitState[ptState->nState];
      if ( v18 )
        v18(ptState, ptQTask);
      v19 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 100;
      v20 = v19[100];
      ptState->pfState = v20;
      v20(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20) != 0 )
    {
      v21 = ptState->apfExitState[ptState->nState];
      if ( v21 )
        v21(ptState, ptQTask);
      v22 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 24;
      v23 = v22[24];
      ptState->pfState = v23;
      v23(ptState, ptQTask);
    }
    else if ( (bSignal & 0x40) != 0 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, ptQTask);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 25;
      v26 = v25[25];
      ptState->pfState = v26;
      v26(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100) != 0 )
    {
      v27 = ptState->apfExitState[ptState->nState];
      if ( v27 )
        v27(ptState, ptQTask);
      v28 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 26;
      v29 = v28[26];
      ptState->pfState = v29;
      v29(ptState, ptQTask);
    }
    else if ( (bSignal & 0x80u) != 0 )
    {
      if ( (bSignal & 0x800000) == 0 )
      {
        v33 = ptState->apfExitState[ptState->nState];
        if ( v33 )
          v33(ptState, ptQTask);
        v34 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v35 = *v34;
        ptState->pfState = *v34;
        v35(ptState, ptQTask);
      }
    }
    else
    {
      v30 = ptState->apfExitState[ptState->nState];
      if ( v30 )
        v30(ptState, ptQTask);
      v31 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v32 = *v31;
      ptState->pfState = v32;
      v32(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:2423  [size]
void __cdecl HumanSoldier_InitStateTenseRunLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateTenseRunLeft;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2444  [anchor-mhash]
void __cdecl HumanSoldier_RunStateTenseRunLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  float v36; // [esp+0h] [ebp-10h]

  v36 = *(float *)&ptQTask[75].tQTaskChildren.ptTail * 267.6053161621094;
  Human_MoveOnGround(ptQTask, v36, 1.5707963705062866);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 71;
      v11 = v10[71];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2000) != 0 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 19;
      v14 = v13[19];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 21;
      v17 = v16[21];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100) != 0 )
    {
      v18 = ptState->apfExitState[ptState->nState];
      if ( v18 )
        v18(ptState, ptQTask);
      v19 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 26;
      v20 = v19[26];
      ptState->pfState = v20;
      v20(ptState, ptQTask);
    }
    else if ( (bSignal & 0x80u) == 0 )
    {
      if ( (bSignal & 0x40) != 0 )
      {
        v24 = ptState->apfExitState[ptState->nState];
        if ( v24 )
          v24(ptState, ptQTask);
        v25 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 25;
        v26 = v25[25];
        ptState->pfState = v26;
        v26(ptState, ptQTask);
      }
      else if ( (bSignal & 0x20) != 0 )
      {
        if ( (bSignal & 0x800000) != 0 )
        {
          if ( (bSignal & 0x40000000) != 0 )
          {
            v33 = ptState->apfExitState[ptState->nState];
            if ( v33 )
              v33(ptState, ptQTask);
            v34 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 8;
            v35 = v34[8];
            ptState->pfState = v35;
            v35(ptState, ptQTask);
          }
        }
        else
        {
          v30 = ptState->apfExitState[ptState->nState];
          if ( v30 )
            v30(ptState, ptQTask);
          v31 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 0;
          v32 = *v31;
          ptState->pfState = v32;
          v32(ptState, ptQTask);
        }
      }
      else
      {
        v27 = ptState->apfExitState[ptState->nState];
        if ( v27 )
          v27(ptState, ptQTask);
        v28 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v29 = *v28;
        ptState->pfState = *v28;
        v29(ptState, ptQTask);
      }
    }
    else
    {
      v21 = ptState->apfExitState[ptState->nState];
      if ( v21 )
        v21(ptState, ptQTask);
      v22 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v23 = v22[23];
      ptState->pfState = v23;
      v23(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:2480  [size]
void __cdecl HumanSoldier_InitStateTenseRunRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateTenseRunRight;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2501  [anchor-mhash]
void __cdecl HumanSoldier_RunStateTenseRunRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  signed int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  float v36; // [esp+0h] [ebp-10h]

  v36 = *(float *)&ptQTask[75].tQTaskChildren.ptTail * 267.6053161621094;
  Human_MoveOnGround(ptQTask, v36, -1.5707963705062866);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 71;
      v11 = v10[71];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2000) != 0 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 19;
      v14 = v13[19];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 21;
      v17 = v16[21];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20) != 0 )
    {
      v18 = ptState->apfExitState[ptState->nState];
      if ( v18 )
        v18(ptState, ptQTask);
      v19 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 24;
      v20 = v19[24];
      ptState->pfState = v20;
      v20(ptState, ptQTask);
    }
    else if ( (bSignal & 0x80u) == 0 )
    {
      if ( (bSignal & 0x100) != 0 )
      {
        v24 = ptState->apfExitState[ptState->nState];
        if ( v24 )
          v24(ptState, ptQTask);
        v25 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 26;
        v26 = v25[26];
        ptState->pfState = v26;
        v26(ptState, ptQTask);
      }
      else if ( (bSignal & 0x40) != 0 )
      {
        if ( (bSignal & 0x800000) != 0 )
        {
          if ( bSignal < 0 )
          {
            v33 = ptState->apfExitState[ptState->nState];
            if ( v33 )
              v33(ptState, ptQTask);
            v34 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 9;
            v35 = v34[9];
            ptState->pfState = v35;
            v35(ptState, ptQTask);
          }
        }
        else
        {
          v30 = ptState->apfExitState[ptState->nState];
          if ( v30 )
            v30(ptState, ptQTask);
          v31 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 0;
          v32 = *v31;
          ptState->pfState = v32;
          v32(ptState, ptQTask);
        }
      }
      else
      {
        v27 = ptState->apfExitState[ptState->nState];
        if ( v27 )
          v27(ptState, ptQTask);
        v28 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v29 = *v28;
        ptState->pfState = *v28;
        v29(ptState, ptQTask);
      }
    }
    else
    {
      v21 = ptState->apfExitState[ptState->nState];
      if ( v21 )
        v21(ptState, ptQTask);
      v22 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v23 = v22[23];
      ptState->pfState = v23;
      v23(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:2538  [size]
void __cdecl HumanSoldier_InitStateTenseRunBackward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateTenseRunBackward;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2559  [anchor-mhash]
void __cdecl HumanSoldier_RunStateTenseRunBackward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  float v33; // [esp+0h] [ebp-10h]

  v33 = *(float *)&ptQTask[75].tQTaskChildren.ptTail * 458.75201416015625;
  Human_MoveOnGround(ptQTask, v33, 3.1415927410125732);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 71;
      v11 = v10[71];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2000) != 0 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 19;
      v14 = v13[19];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 21;
      v17 = v16[21];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20) != 0 )
    {
      v18 = ptState->apfExitState[ptState->nState];
      if ( v18 )
        v18(ptState, ptQTask);
      v19 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 24;
      v20 = v19[24];
      ptState->pfState = v20;
      v20(ptState, ptQTask);
    }
    else if ( (bSignal & 0x80u) == 0 )
    {
      if ( (bSignal & 0x40) != 0 )
      {
        v24 = ptState->apfExitState[ptState->nState];
        if ( v24 )
          v24(ptState, ptQTask);
        v25 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 25;
        v26 = v25[25];
        ptState->pfState = v26;
        v26(ptState, ptQTask);
      }
      else if ( (bSignal & 0x100) != 0 )
      {
        if ( (bSignal & 0x800000) == 0 )
        {
          v30 = ptState->apfExitState[ptState->nState];
          if ( v30 )
            v30(ptState, ptQTask);
          v31 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 0;
          v32 = *v31;
          ptState->pfState = v32;
          v32(ptState, ptQTask);
        }
      }
      else
      {
        v27 = ptState->apfExitState[ptState->nState];
        if ( v27 )
          v27(ptState, ptQTask);
        v28 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v29 = *v28;
        ptState->pfState = *v28;
        v29(ptState, ptQTask);
      }
    }
    else
    {
      v21 = ptState->apfExitState[ptState->nState];
      if ( v21 )
        v21(ptState, ptQTask);
      v22 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v23 = v22[23];
      ptState->pfState = v23;
      v23(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:2595  [anchor-mhash]
void __cdecl HumanSoldier_InitStateRunForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  int v3; // ebx
  struct QTask_s *ptNext; // edx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // ecx
  struct QTask_s *v9; // esi
  struct QTask_s *v10; // eax
  char *p_ptMiddle; // ebp
  char *v12; // [esp-Ch] [ebp-14h]

  ptParent = ptQTask[74].ptParent;
  v3 = 5;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 1;
  if ( ((unsigned __int8)ptParent & 1) != 0 )
  {
    ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  }
  ptNext = ptQTask[33].ptNext;
  if ( ptNext )
  {
    ptPrev = ptNext[1].ptPrev;
    if ( ptPrev )
    {
      ptTail = ptPrev->tQTaskChildren.ptTail;
      if ( ptTail )
      {
        v7 = ptQTask[7].tQTaskRefList.ptTail == *(struct QReference_s **)&ptTail[48].tQTaskChildren.ptHead[24].eQTaskType
           ? ptTail[48].tQTaskChildren.ptHead
           : ptTail[48].tQTaskChildren.ptMiddle;
        if ( v7 )
        {
          v8 = ptNext[1].ptPrev;
          v9 = v8 ? v8->tQTaskChildren.ptTail : nullptr;
          v10 = v7[1].tQTaskChildren.ptTail;
          if ( v10 )
          {
            switch ( (unsigned int)v9[16].tQTaskRefList.ptTail )
            {
              case 0u:
              case 2u:
                v12 = (char *)&dword_68FF78;
                goto LABEL_18;
              case 1u:
                v12 = (char *)&dword_68FF70;
                goto LABEL_18;
              case 3u:
                v12 = dword_68FF68;
LABEL_18:
                p_ptMiddle = (char *)&v10[1].tQTaskChildren.ptMiddle;
                if ( strstr((char *)&v10[1].tQTaskChildren.ptMiddle, v12)
                  || strstr(p_ptMiddle, (char *)&v9[10].tQTaskChildren.ptMiddle) )
                {
                  ptQTask[74].ptParent = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
                  v3 = 4;
                  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
                }
                break;
              default:
                break;
            }
          }
        }
      }
    }
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, v3, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateRunForward;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2669  [anchor-mhash]
void __cdecl HumanSoldier_RunStateRunForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  int v3; // edi
  struct QTask_s *ptParent; // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // edi
  float v8; // [esp+0h] [ebp-14h]

  v8 = *(float *)&ptQTask[75].tQTaskChildren.ptTail * 458.75201416015625;
  Human_MoveOnGround(ptQTask, v8, 0.0);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v3 = 41;
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v3 = 71;
    }
    else if ( (bSignal & 0x2000) != 0 )
    {
      v3 = 19;
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v3 = 21;
    }
    else if ( (bSignal & 0x2000000) != 0 )
    {
      v3 = 12;
    }
    else if ( (bSignal & 0x800000) != 0 )
    {
      v3 = 23;
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v3 = 6;
    }
    else if ( (bSignal & 0x20) != 0 )
    {
      v3 = 24;
    }
    else if ( (bSignal & 0x40) != 0 )
    {
      v3 = 25;
    }
    else if ( (bSignal & 0x100) != 0 )
    {
      v3 = 26;
    }
    else
    {
      if ( (bSignal & 0x80u) != 0 )
        return;
      v3 = 0;
    }
  }
  else
  {
    v3 = 39;
  }
  ptParent = ptQTask[74].ptParent;
  if ( ((unsigned __int8)ptParent & 1) != 0 )
  {
    ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  }
  v5 = ptState->apfExitState[ptState->nState];
  if ( v5 )
    v5(ptState, ptQTask);
  apfState = ptState->apfState;
  ptState->nPreviousState = ptState->nState;
  ptState->nState = v3;
  v7 = apfState[v3];
  ptState->pfState = v7;
  v7(ptState, ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:2751  [anchor-mhash]
void __cdecl HumanSoldier_InitStateWalkForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // ecx
  int v3; // ebp
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // ecx
  struct QTask_s *v8; // esi
  struct QTask_s *ptMiddle; // eax
  char *p_ptMiddle; // ebx
  struct QTask_s *ptParent; // eax
  char *v12; // [esp-4h] [ebp-14h]

  ptNext = ptQTask[33].ptNext;
  v3 = 0;
  if ( ptNext )
  {
    ptPrev = ptNext[1].ptPrev;
    if ( ptPrev )
    {
      ptTail = ptPrev->tQTaskChildren.ptTail;
      if ( ptTail )
      {
        v6 = ptQTask[7].tQTaskRefList.ptTail == *(struct QReference_s **)&ptTail[48].tQTaskChildren.ptHead[24].eQTaskType
           ? ptTail[48].tQTaskChildren.ptHead
           : ptTail[48].tQTaskChildren.ptMiddle;
        if ( v6 )
        {
          v7 = ptNext[1].ptPrev;
          v8 = v7 ? v7->tQTaskChildren.ptTail : nullptr;
          ptMiddle = v6[1].tQTaskChildren.ptMiddle;
          if ( ptMiddle )
          {
            switch ( (unsigned int)v8[16].tQTaskRefList.ptTail )
            {
              case 0u:
              case 2u:
                v12 = (char *)&dword_68FF78;
                goto LABEL_16;
              case 1u:
                v12 = (char *)&dword_68FF70;
                goto LABEL_16;
              case 3u:
                v12 = dword_68FF68;
LABEL_16:
                p_ptMiddle = (char *)&ptMiddle[1].tQTaskChildren.ptMiddle;
                if ( strstr((char *)&ptMiddle[1].tQTaskChildren.ptMiddle, v12)
                  || strstr(p_ptMiddle, (char *)&v8[10].tQTaskChildren.ptMiddle) )
                {
                  v3 = 1;
                }
                break;
              default:
                break;
            }
          }
        }
      }
    }
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 7, 0, 0.0);
  if ( v3 )
  {
    ptQTask[74].ptParent = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
LABEL_23:
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_24;
  }
  ptParent = ptQTask[74].ptParent;
  if ( ((unsigned __int8)ptParent & 1) != 0 )
  {
    ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
    goto LABEL_23;
  }
LABEL_24:
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 0;
  ptState->pfState = HumanSoldier_RunStateWalkForward;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2826  [anchor-mhash]
void __cdecl HumanSoldier_RunStateWalkForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  int v3; // edi
  struct QTask_s *ptParent; // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // edi
  float v8; // [esp+0h] [ebp-14h]

  v8 = *(float *)&ptQTask[75].tQTaskChildren.ptTail * 204.8000030517578;
  Human_MoveOnGround(ptQTask, v8, 0.0);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v3 = 41;
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v3 = 71;
    }
    else if ( (bSignal & 0x2000) != 0 )
    {
      v3 = 19;
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v3 = 21;
    }
    else if ( (bSignal & 0x2000000) != 0 )
    {
      v3 = 12;
    }
    else if ( (bSignal & 0x20) != 0 )
    {
      v3 = 24;
    }
    else if ( (bSignal & 0x40) != 0 )
    {
      v3 = 25;
    }
    else if ( (bSignal & 0x100) != 0 )
    {
      v3 = 26;
    }
    else if ( (bSignal & 0x800000) != 0 )
    {
      v3 = 23;
    }
    else if ( (bSignal & 0x80u) != 0 )
    {
      if ( (bSignal & 0x40000) != 0 )
        return;
      v3 = 5;
    }
    else
    {
      v3 = 0;
    }
  }
  else
  {
    v3 = 39;
  }
  ptParent = ptQTask[74].ptParent;
  if ( ((unsigned __int8)ptParent & 1) != 0 )
  {
    ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  }
  v5 = ptState->apfExitState[ptState->nState];
  if ( v5 )
    v5(ptState, ptQTask);
  apfState = ptState->apfState;
  ptState->nPreviousState = ptState->nState;
  ptState->nState = v3;
  v7 = apfState[v3];
  ptState->pfState = v7;
  v7(ptState, ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:2906  [size]
void __cdecl HumanSoldier_InitStateStandRollLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptQTask[74].ptParent = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateStandRollLeft;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2928  [size]
void __cdecl HumanSoldier_RunStateStandRollLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptParent; // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax

  Human_MoveOnGround(ptQTask, 382.2933349609375, 1.5707963705062866);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v8 = apfState[55];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      ptParent = ptQTask[74].ptParent;
      if ( ((unsigned __int8)ptParent & 1) != 0 )
      {
        ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      }
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, ptQTask);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 27;
      v12 = v11[27];
      ptState->pfState = v12;
      v12(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:2959  [size]
void __cdecl HumanSoldier_InitStateStandRollRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptQTask[74].ptParent = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateStandRollRight;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:2981  [size]
void __cdecl HumanSoldier_RunStateStandRollRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptParent; // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax

  Human_MoveOnGround(ptQTask, 382.2933349609375, -1.5707963705062866);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v8 = apfState[55];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      ptParent = ptQTask[74].ptParent;
      if ( ((unsigned __int8)ptParent & 1) != 0 )
      {
        ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      }
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, ptQTask);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 27;
      v12 = v11[27];
      ptState->pfState = v12;
      v12(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3013  [size]
void __cdecl HumanSoldier_InitStateStandThrowGrenade(struct State_s *ptState, struct QTask_s *ptQTask)
{
  double *ptParent; // esi
  double v3; // st7
  int v4; // ebx
  double v5; // st5
  double v6; // [esp+10h] [ebp-8h]

  ptParent = (double *)ptQTask[48].ptParent;
  BYTE2(ptQTask[75].tQTaskRefList.ptTail) = 0;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptQTask[74].ptParent = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  v3 = ptParent[3740] - *(double *)&ptQTask[1].ptNext;
  v4 = 13;
  v6 = ptParent[3742] - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  v5 = ptParent[3741] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  if ( sqrt(v3 * v3 + v5 * v5 + v6 * v6) >= 20480.0 )
    v4 = 12;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, v4, 0, 0.0);
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  ptState->pfState = HumanSoldier_RunStateStandThrowGrenade;
  if ( !CDAPFN0506_HumanSoldier_InitStateStandThrowGrenade.Version )
    ((void (*)(void))CDAPFN0506_HumanSoldier_InitStateStandThrowGrenade.FunctionAddress)();
}

// source: j/0/human/soldiertypes/humansoldier.c:3052  [anchor-caller]
void __cdecl HumanSoldier_RunStateStandThrowGrenade(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v15; };
    struct { char igi2_o1[4]; char v16; };
    struct { char igi2_o2[8]; struct real32x3_t *ptGrenadeSpeed; };
    struct { char igi2_o3[12]; struct real32x9_t ptGrenadeOrientation; };
    struct { char igi2_o4[56]; int v19; };
    struct { char igi2_o5[60]; struct QTask_s *v20; };
    struct { char igi2_o6[88]; struct real64x3_t ptPos; };
    struct { char igi2_o7[112]; struct real32x9_t ptOrientation; };
    char igi2_extent[156];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct State_s *v2; // esi
  unsigned int bSignal; // eax
  unsigned __int8 *ptTail; // ecx
  int Bone; // eax
  struct real32x3_t *v6; // ebx
  struct WeaponType_s *WeaponTypeFromID; // esi
  struct PhysicsObjType_s *Type; // eax
  _DWORD *v9; // edi
  struct QReference_s *v10; // eax
  struct QTask_s *ptParent; // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax

  v2 = ptState;
  igi2_frame.ptGrenadeSpeed = (struct real32x3_t *)ptQTask[48].ptParent;
  bSignal = ptState->bSignal;
  igi2_frame.v15 = -1;
  igi2_frame.v16 = bSignal;
  if ( (bSignal & 2) == 0 )
    igi2_frame.v15 = 39;
  if ( (bSignal & 0x10000) != 0 )
    igi2_frame.v15 = 41;
  if ( (bSignal & 0x20000) != 0 )
    igi2_frame.v15 = 71;
  if ( (bSignal & 0x8000000) != 0 && !BYTE2(ptQTask[75].tQTaskRefList.ptTail) )
  {
    ptTail = (unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail;
    *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x8000000u;
    Bone = Hierarchy_GetBone(ptTail, "right hand");
    BoneDynCubeObj_GetBonePosition((struct BoneDynCubeObj_s *)&igi2_frame.ptPos, (struct real32x3_t *)ptQTask, Bone);
    v6 = igi2_frame.ptGrenadeSpeed;
    if ( HumanAI_GetGrenadeOrientationAndSpeedToTarget(
           &igi2_frame.ptOrientation,
           &igi2_frame.ptGrenadeOrientation.tX,
           (struct HumanAI_s *)igi2_frame.ptGrenadeSpeed,
           &igi2_frame.ptPos,
           (int *)&igi2_frame.ptGrenadeSpeed) )
    {
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(LODWORD(v6[2493].vX));
      Type = PhysicsObjType_FindType(WeaponTypeFromID->zFixedModel);
      v9 = Type ? Type->pxData : nullptr;
      Grenade_New(
        Level_ptDynamicQTask,
        0,
        ptQTask,
        &igi2_frame.ptPos,
        &igi2_frame.ptOrientation,
        &igi2_frame.ptGrenadeOrientation.tX,
        WeaponTypeFromID,
        (int)&igi2_frame.ptGrenadeSpeed[1].vX + 3);
      HumanAI_PlaySoundAtPosition((struct QTask_s *)v6, "GV_75_01", true);
      BYTE2(ptQTask[75].tQTaskRefList.ptTail) = 1;
      if ( !v9[1] )
      {
        v10 = ptQTask[10].tQTaskRefList.ptTail;
        LODWORD(igi2_frame.ptGrenadeOrientation.tZ.vY) = &v6[2493].vY;
        LODWORD(igi2_frame.ptGrenadeOrientation.tY.vX) = 37;
        LODWORD(igi2_frame.ptGrenadeOrientation.tY.vY) = v10;
        LODWORD(igi2_frame.ptGrenadeOrientation.tY.vZ) = 1314;
        igi2_frame.v19 = 0;
        igi2_frame.v20 = ptQTask;
        igi2_frame.ptGrenadeOrientation.tZ.vX = 40960.0;
        HumanAI_SendEvent((struct HumanAIEventContext_t *)&igi2_frame.ptGrenadeOrientation.tY);
      }
    }
    LOBYTE(bSignal) = igi2_frame.v16;
    v2 = ptState;
  }
  if ( (bSignal & 1) != 0 )
  {
    igi2_frame.v15 = 0;
  }
  else if ( igi2_frame.v15 == -1 )
  {
    return;
  }
  ptParent = ptQTask[74].ptParent;
  if ( ((unsigned __int8)ptParent & 1) != 0 )
  {
    ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  }
  v12 = v2->apfExitState[v2->nState];
  if ( v12 )
    v12(v2, ptQTask);
  apfState = v2->apfState;
  v2->nPreviousState = v2->nState;
  v2->nState = igi2_frame.v15;
  v14 = apfState[igi2_frame.v15];
  v2->pfState = v14;
  v14(v2, ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:3181  [anchor-mhash]
void __cdecl HumanSoldier_InitStateStandCloseCombat(struct State_s *ptState, struct QTask_s *ptQTask)
{
  HIBYTE(ptQTask[75].tQTaskRefList.ptTail) = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateStandCloseCombat;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3200  [anchor-mhash]
void __cdecl HumanSoldier_RunStateStandCloseCombat(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 71;
      v11 = v10[71];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else
    {
      if ( (bSignal & 0x10000000) != 0 && !HIBYTE(ptQTask[75].tQTaskRefList.ptTail) )
      {
        *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x10000000u;
        HIBYTE(ptQTask[75].tQTaskRefList.ptTail) = 1;
      }
      if ( (bSignal & 1) != 0 )
      {
        v12 = ptState->apfExitState[ptState->nState];
        if ( v12 )
          v12(ptState, ptQTask);
        v13 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v14 = *v13;
        ptState->pfState = v14;
        v14(ptState, ptQTask);
      }
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3258  [size]
void __cdecl HumanSoldier_InitStateStandToKneel(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateStandToKneel;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3276  [size]
void __cdecl HumanSoldier_RunStateStandToKneel(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v8 = apfState[55];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 27;
      v11 = v10[27];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3297  [size]
void __cdecl HumanSoldier_InitStateKneelToStand(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateKneelToStand;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3315  [size]
void __cdecl HumanSoldier_RunStateKneelToStand(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v8 = apfState[55];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v11 = *v10;
      ptState->pfState = *v10;
      v11(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3336  [size]
void __cdecl HumanSoldier_InitStateStandToLieDown(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 2;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateStandToLieDown;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3353  [size]
void __cdecl HumanSoldier_RunStateStandToLieDown(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 45;
      v8 = apfState[45];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v11 = v10[36];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3374  [size]
void __cdecl HumanSoldier_InitStateLieDownToStand(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 2;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateLieDownToStand;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3391  [anchor-mhash]
void __cdecl HumanSoldier_RunStateLieDownToStand(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                             + (double)AnimController_nTicksPerFrame);
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 45;
      v8 = apfState[45];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v11 = *v10;
      ptState->pfState = *v10;
      v11(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3413  [size]
void __cdecl HumanSoldier_InitStateKneel(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 28, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateKneel;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3430  [anchor-mhash]
void __cdecl HumanSoldier_RunStateKneel(struct State_s *ptState, struct QTask_s *ptQTask)
{
  signed int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v11 = v10[55];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 35;
      v14 = v13[35];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2008) != 0 )
    {
      if ( (bSignal & 0x20000000) != 0 )
      {
        v18 = ptState->apfExitState[ptState->nState];
        if ( v18 )
          v18(ptState, ptQTask);
        v19 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 29;
        v20 = v19[29];
        ptState->pfState = v20;
        v20(ptState, ptQTask);
      }
      else if ( (bSignal & 0x1E0) != 0 )
      {
        v21 = ptState->apfExitState[ptState->nState];
        if ( v21 )
          v21(ptState, ptQTask);
        v22 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 20;
        v23 = v22[20];
        ptState->pfState = v23;
        v23(ptState, ptQTask);
      }
      else if ( (bSignal & 0x40000000) != 0 )
      {
        v24 = ptState->apfExitState[ptState->nState];
        if ( v24 )
          v24(ptState, ptQTask);
        v25 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 30;
        v26 = v25[30];
        ptState->pfState = v26;
        v26(ptState, ptQTask);
      }
      else if ( bSignal < 0 )
      {
        v27 = ptState->apfExitState[ptState->nState];
        if ( v27 )
          v27(ptState, ptQTask);
        v28 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 31;
        v29 = v28[31];
        ptState->pfState = v29;
        v29(ptState, ptQTask);
      }
    }
    else
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 20;
      v17 = v16[20];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3462  [size]
void __cdecl HumanSoldier_InitStateKneelTurn(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 29, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateKneelTurn;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3479  [anchor-mhash]
void __cdecl HumanSoldier_RunStateKneelTurn(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v11 = v10[55];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 35;
      v14 = v13[35];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x2008) != 0 )
    {
      if ( (bSignal & 0x20000000) != 0 )
      {
        if ( (bSignal & 0x1E0) != 0 )
        {
          v21 = ptState->apfExitState[ptState->nState];
          if ( v21 )
            v21(ptState, ptQTask);
          v22 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 20;
          v23 = v22[20];
          ptState->pfState = v23;
          v23(ptState, ptQTask);
        }
      }
      else
      {
        v18 = ptState->apfExitState[ptState->nState];
        if ( v18 )
          v18(ptState, ptQTask);
        v19 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 27;
        v20 = v19[27];
        ptState->pfState = v20;
        v20(ptState, ptQTask);
      }
    }
    else
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 20;
      v17 = v16[20];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3510  [size]
void __cdecl HumanSoldier_InitStateKneelRollLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *v2; // ecx

  v2 = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  ptQTask[74].ptParent = v2;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateKneelRollLeft;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:3531  [size]
void __cdecl HumanSoldier_RunStateKneelRollLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptParent; // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax

  Human_MoveOnGround(ptQTask, 382.2933349609375, 1.5707963705062866);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v8 = apfState[55];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      ptParent = ptQTask[74].ptParent;
      if ( ((unsigned __int8)ptParent & 1) != 0 )
      {
        ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      }
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, ptQTask);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 27;
      v12 = v11[27];
      ptState->pfState = v12;
      v12(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3561  [size]
void __cdecl HumanSoldier_InitStateKneelRollRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *v2; // ecx

  v2 = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  ptQTask[74].ptParent = v2;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateKneelRollRight;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:3582  [size]
void __cdecl HumanSoldier_RunStateKneelRollRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptParent; // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax

  Human_MoveOnGround(ptQTask, 382.2933349609375, -1.5707963705062866);
  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v8 = apfState[55];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      ptParent = ptQTask[74].ptParent;
      if ( ((unsigned __int8)ptParent & 1) != 0 )
      {
        ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      }
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, ptQTask);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 27;
      v12 = v11[27];
      ptState->pfState = v12;
      v12(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3614  [size]
void __cdecl HumanSoldier_InitStateKneelToLieDown(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateKneelToLieDown;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3631  [size]
void __cdecl HumanSoldier_RunStateKneelToLieDown(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v8 = apfState[55];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v11 = v10[36];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3652  [anchor-mhash]
void __cdecl HumanSoldier_InitStateLieDown(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 2;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateLieDown;
}

// source: j/0/human/soldiertypes/humansoldier.c:3670  [anchor-mhash]
void __cdecl HumanSoldier_RunStateLieDown(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 42;
      v8 = apfState[42];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 45;
      v11 = v10[45];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x100000) != 0 )
    {
      if ( (bSignal & 0x200) != 0 )
      {
        v15 = ptState->apfExitState[ptState->nState];
        if ( v15 )
          v15(ptState, ptQTask);
        v16 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 37;
        v17 = v16[37];
        ptState->pfState = v17;
        v17(ptState, ptQTask);
      }
      else if ( (bSignal & 0x800) != 0 )
      {
        v18 = ptState->apfExitState[ptState->nState];
        if ( v18 )
          v18(ptState, ptQTask);
        v19 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 38;
        v20 = v19[38];
        ptState->pfState = v20;
        v20(ptState, ptQTask);
      }
    }
    else
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 22;
      v14 = v13[22];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3696  [size]
void __cdecl HumanSoldier_InitStateLieDownFire(struct State_s *ptState, struct QTask_s *ptQTask)
{
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateLieDownFire;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3710  [anchor-mhash]
void __cdecl HumanSoldier_RunStateLieDownFire(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // ebx
  struct QTask_s *ptNext; // eax
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *v7; // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *v11; // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *v15; // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 0x20000) != 0 )
  {
    ptNext = ptQTask[33].ptNext;
    ptNext[2].ptParent = (struct QTask_s *)1;
    ptNext[1].tQTaskChildren.ptTail = nullptr;
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 45;
    v6 = apfState[45];
    ptState->pfState = v6;
    v6(ptState, ptQTask);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v11 = ptQTask[33].ptNext;
      v11[2].ptParent = (struct QTask_s *)1;
      v11[1].tQTaskChildren.ptTail = nullptr;
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 42;
      v14 = v13[42];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else
    {
      if ( *(float *)&ptQTask[19].tQTaskRefList.ptTail != 0.0 )
        Weapon_Fire(ptQTask[33].ptNext, 0);
      if ( (bSignal & 1) != 0 && (bSignal & 0x200) == 0 )
      {
        v15 = ptQTask[33].ptNext;
        v15[2].ptParent = (struct QTask_s *)1;
        v15[1].tQTaskChildren.ptTail = nullptr;
        v16 = ptState->apfExitState[ptState->nState];
        if ( v16 )
          v16(ptState, ptQTask);
        v17 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v18 = v17[36];
        ptState->pfState = v18;
        v18(ptState, ptQTask);
      }
    }
  }
  else
  {
    v7 = ptQTask[33].ptNext;
    v7[2].ptParent = (struct QTask_s *)1;
    v7[1].tQTaskChildren.ptTail = nullptr;
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, ptQTask);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v10 = v9[39];
    ptState->pfState = v10;
    v10(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3763  [size]
void __cdecl HumanSoldier_InitStateLieDownReload(struct State_s *ptState, struct QTask_s *ptQTask)
{
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateLieDownReload;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:3777  [anchor-mhash]
void __cdecl HumanSoldier_RunStateLieDownReload(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptNext; // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 42;
      v8 = apfState[42];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 45;
      v11 = v10[45];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      ptNext = ptQTask[33].ptNext;
      if ( ptNext )
        Weapon_Reload(ptNext);
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, ptQTask);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v15 = v14[36];
      ptState->pfState = v15;
      v15(ptState, ptQTask);
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3810  [anchor-mhash]
void __cdecl HumanSoldier_InitStateFall(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *v2; // eax

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  BYTE1(ptQTask[50].ptNext) = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptQTask[38].ptPrev = (struct QTask_s *)ptQTask[38].tQTaskRefList.ptTail;
  v2 = *(struct QTask_s **)&ptQTask[38].eQTaskType;
  ptQTask[38].tQTaskChildren.ptHead = ptQTask[38].ptParent;
  ptQTask[38].tQTaskChildren.ptMiddle = v2;
  ptState->pfState = HumanSoldier_RunStateFall;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:3831  [anchor-mhash]
void __cdecl HumanSoldier_RunStateFall(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v7)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v10; // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax

  *(float *)&ptQTask[38].ptPrev = *(float *)&ptQTask[38].ptPrev * 0.9900000095367432;
  *(float *)&ptQTask[38].tQTaskChildren.ptHead = *(float *)&ptQTask[38].tQTaskChildren.ptHead * 0.9900000095367432;
  *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = (*(float *)&ptQTask[38].tQTaskChildren.ptMiddle - 84.74169158935547)
                                                 * 0.9900000095367432;
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x10000) != 0 )
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 41;
    v5 = apfState[41];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
  else if ( (bSignal & 0x20000) != 0 )
  {
    v6 = ptState->apfExitState[ptState->nState];
    if ( v6 )
      v6(ptState, ptQTask);
    v7 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 71;
    v8 = v7[71];
    ptState->pfState = v8;
    v8(ptState, ptQTask);
  }
  else if ( (bSignal & 2) != 0 )
  {
    ptMiddle = ptQTask[42].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
    {
      v10 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)&ptMiddle[49].pxObject);
      if ( v10 )
        SoundSys_SetSoundPosition(v10, (struct real64x3_t *)&ptQTask[40].ptParent);
    }
    ptQTask[38].ptPrev = nullptr;
    ptQTask[38].tQTaskChildren.ptHead = nullptr;
    ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, ptQTask);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v13 = *v12;
    ptState->pfState = *v12;
    v13(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:3887  [anchor-mhash]
void __cdecl HumanSoldier_InitStateHit(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct Game_s *v2; // eax
  unsigned int v3; // ecx
  unsigned int v4; // esi
  unsigned int v5; // edx
  unsigned int v6; // edx
  int v7; // ebx
  struct QReference_s *v8; // esi
  struct QTask_s *ptParent; // eax
  int v10; // eax
  int ptPrev; // esi
  int pxObject; // esi
  unsigned int v13; // [esp+Ch] [ebp-4h]

  v2 = Game_ptGame;
  v3 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  v4 = v3 ^ Game_ptGame->tRunRandomState.anRandom[1];
  Game_ptGame->tRunRandomState.anRandom[2] = v3;
  v5 = v4 + v2->tRunRandomState.anRandom[0];
  v2->tRunRandomState.anRandom[1] = v4;
  v2->tRunRandomState.anRandom[0] = v5;
  v6 = v5 % 3;
  v7 = 0;
  v8 = &ptQTask[25].tQTaskRefList.ptTail[5 * (int)ptQTask[29].tQTaskChildren.ptHead];
  v13 = v6;
  switch ( (unsigned int)ptQTask[29].tQTaskChildren.ptHead )
  {
    case 0u:
    case 1u:
    case 2u:
    case 6u:
    case 7u:
    case 8u:
      v7 = 0;
      break;
    case 3u:
    case 4u:
    case 5u:
    case 9u:
    case 0xAu:
    case 0xBu:
    case 0xCu:
    case 0xDu:
    case 0xEu:
    case 0xFu:
    case 0x10u:
      v7 = 1;
      break;
    default:
      break;
  }
  ptParent = ptQTask[74].ptParent;
  if ( ((unsigned __int8)ptParent & 1) != 0 )
  {
    ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    v6 = v13;
  }
  if ( *(float *)&ptQTask[75].tQTaskChildren.ptMiddle < (double)*(float *)&ptQTask[75].tQTaskChildren.ptHead
    || LOBYTE(ptQTask[75].tQTaskRefList.ptTail) )
  {
    v10 = *(_DWORD *)&ptQTask[32].eQTaskType;
    if ( v7 )
    {
      ptPrev = *((_DWORD *)&v8->pxObject + v6);
      goto LABEL_10;
    }
    if ( v10 == 1 )
      pxObject = 27;
    else
      pxObject = *((_DWORD *)&v8->pxObject + v6);
LABEL_15:
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, pxObject, 0, 0.0);
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 102, 0, 0.0);
    ptState->pfState = HumanSoldier_RunStateHitLowerBody;
    goto LABEL_16;
  }
  v10 = *(_DWORD *)&ptQTask[32].eQTaskType;
  LOBYTE(ptQTask[75].tQTaskRefList.ptTail) = 1;
  if ( !v7 )
  {
    if ( v10 == 1 )
      pxObject = (int)v8[3].pxObject;
    else
      pxObject = (int)v8->ptPrev;
    goto LABEL_15;
  }
  ptPrev = (int)v8->ptPrev;
LABEL_10:
  if ( !v10 )
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 103, 0, 0.0);
  HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, ptPrev, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateHitUpperBody;
LABEL_16:
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:4029  [anchor-mhash]
void __cdecl HumanSoldier_RunStateHitLowerBody(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
      {
        v6 = ptState->apfExitState[ptState->nState];
        if ( v6 )
          v6(ptState, ptQTask);
        apfState = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 55;
        v8 = apfState[55];
        ptState->pfState = v8;
        v8(ptState, ptQTask);
      }
      else
      {
        v9 = ptState->apfExitState[ptState->nState];
        if ( v9 )
          v9(ptState, ptQTask);
        v10 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 71;
        v11 = v10[71];
        ptState->pfState = v11;
        v11(ptState, ptQTask);
      }
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v14 = v13[41];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 1) != 0 )
    {
      LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
      if ( (bSignal & 0x2000) != 0 )
      {
        v15 = ptState->apfExitState[ptState->nState];
        if ( v15 )
          v15(ptState, ptQTask);
        v16 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 27;
        v17 = v16[27];
        ptState->pfState = v17;
        v17(ptState, ptQTask);
      }
      else
      {
        v18 = ptState->apfExitState[ptState->nState];
        if ( v18 )
          v18(ptState, ptQTask);
        v19 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v20 = *v19;
        ptState->pfState = *v19;
        v20(ptState, ptQTask);
      }
    }
    else if ( (bSignal & 0x10) != 0 )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 102, 0, 0.0);
    }
  }
  else
  {
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:4084  [anchor-mhash]
void __cdecl HumanSoldier_RunStateHitUpperBody(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
      {
        v6 = ptState->apfExitState[ptState->nState];
        if ( v6 )
          v6(ptState, ptQTask);
        apfState = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 55;
        v8 = apfState[55];
        ptState->pfState = v8;
        v8(ptState, ptQTask);
      }
      else
      {
        v9 = ptState->apfExitState[ptState->nState];
        if ( v9 )
          v9(ptState, ptQTask);
        v10 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 71;
        v11 = v10[71];
        ptState->pfState = v11;
        v11(ptState, ptQTask);
      }
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v14 = v13[41];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( (bSignal & 0x10) != 0 )
    {
      LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
      if ( (bSignal & 0x2000) != 0 )
      {
        v15 = ptState->apfExitState[ptState->nState];
        if ( v15 )
          v15(ptState, ptQTask);
        v16 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 27;
        v17 = v16[27];
        ptState->pfState = v17;
        v17(ptState, ptQTask);
      }
      else
      {
        v18 = ptState->apfExitState[ptState->nState];
        if ( v18 )
          v18(ptState, ptQTask);
        v19 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v20 = *v19;
        ptState->pfState = *v19;
        v20(ptState, ptQTask);
      }
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:4144  [anchor-mhash]
void __cdecl HumanSoldier_InitStateLieDownHit(struct State_s *ptState, struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[75].tQTaskRefList.ptMiddle = nullptr;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
  ptState->pfState = HumanSoldier_RunStateLieDownHit;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:4171  [anchor-mhash]
void __cdecl HumanSoldier_RunStateLieDownHit(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // ecx
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v7)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  struct QReference_s *ptMiddle; // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) == 0 )
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = apfState[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 0x20000) != 0 )
  {
    v6 = ptState->apfExitState[ptState->nState];
    if ( v6 )
      v6(ptState, ptQTask);
    v7 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 45;
    v8 = v7[45];
    ptState->pfState = v8;
    v8(ptState, ptQTask);
    return;
  }
  ptMiddle = ptQTask[75].tQTaskRefList.ptMiddle;
  if ( (int)ptMiddle <= 19 )
  {
    ptQTask[75].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)&ptMiddle->ptNext + 1);
  }
  else if ( (bSignal & 0x10000) != 0 )
  {
    v10 = ptState->apfExitState[ptState->nState];
    if ( v10 )
      v10(ptState, ptQTask);
    v11 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 42;
    v12 = v11[42];
    ptState->pfState = v12;
    v12(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 1) != 0 )
  {
    LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
    v13 = ptState->apfExitState[ptState->nState];
    if ( v13 )
      v13(ptState, ptQTask);
    v14 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v15 = v14[36];
    ptState->pfState = v15;
    v15(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:4214  [anchor-caller]
void __cdecl HumanSoldier_CreateGunPickups(struct HumanSoldier_t *ptHumanSoldier)
{
  struct QTask_s *ptWeaponQTask; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v4; // eax
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // esi
  struct WeaponTypeItem_s *v6; // eax
  struct WeaponType_s *ptTail; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct QReference_s *ptHumanSoldiera = *(struct QReference_s * *)&ptHumanSoldier; // [esp+14h] [ebp+4h] ARGSLOT

  ptWeaponQTask = ptHumanSoldier->tHuman.ptWeaponQTask;
  if ( ptWeaponQTask )
  {
    ptHumanSoldiera = ptHumanSoldier->tHuman.ptHitSoundQTaskRef;
    ptPrev = ptWeaponQTask[1].ptPrev;
    if ( ptPrev && (v4 = ptPrev->tQTaskChildren.ptTail) != nullptr && !strcmp((char *)&v4[3].eQTaskType, "IR SAM") )
    {
      WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, "WEAPON_ID_RPG_IR");
      v6 = Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, "WEAPON_ID_RPG7");
      v6->isActive = 1;
      WeaponTypeItemFromWeaponType->isActive = 0;
      Human_CreateGunPickupFromGameDifficulty(ptHumanSoldier->tHuman.ptWeaponQTask, v6->ptWeaponType);
    }
    else
    {
      ptTail = (struct WeaponType_s *)ptWeaponQTask[1].ptPrev;
      if ( ptTail )
        ptTail = (struct WeaponType_s *)ptTail->tQTask.tQTaskChildren.ptTail;
      Human_CreateGunPickupFromGameDifficulty(ptWeaponQTask, ptTail);
    }
    if ( LOBYTE(ptHumanSoldiera[2492].ptNext) )
    {
      if ( Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) <= 0.5 )
      {
        WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptHumanSoldiera[2493].ptNext);
        if ( WeaponTypeFromID )
        {
          if ( strcmp(WeaponTypeFromID->zWeaponScriptID, "WEAPON_ID_FLASHBANG") )
            Human_CreateGunPickupFromGameDifficulty(ptHumanSoldier->tHuman.ptWeaponQTask, WeaponTypeFromID);
        }
      }
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:4270  [anchor-mhash]
void __cdecl HumanSoldier_InitStateDie(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int piTask; };
    struct { char igi2_o1[4]; float v34; };
    struct { char igi2_o2[8]; struct QReference_s *ptMiddle; };
    struct { char igi2_o3[12]; float v36; };
    struct { char igi2_o4[16]; _DWORD v37[11]; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // eax
  struct QTaskList_s *v3; // ebx
  double v4; // st7
  struct QReferenceList_s *p_tQTaskRefList; // edi
  double v6; // st6
  double v7; // st5
  struct QTask_s *ptHead; // ebx
  long double v9; // st4
  struct QReference_s *v10; // edx
  struct QReference_s *v11; // eax
  int v12; // ecx
  double v13; // st7
  struct Game_s *v14; // eax
  unsigned int v15; // ebx
  unsigned int v16; // ecx
  int v17; // ecx
  unsigned int v18; // edx
  unsigned int v19; // ebx
  float v20; // eax
  struct QReference_s *ptTail; // edx
  double v22; // st7
  struct QReference_s *v23; // eax
  struct QReference_s *v24; // ecx
  int v25; // edi
  float v26; // edx
  struct QReference_s *v27; // ecx
  struct QTask_s *v28; // eax
  double v29; // st7
  double v30; // st6
  struct QTask_s *v31; // eax
  struct QTask_s *v32; // edx

  ptNext = ptQTask[33].ptNext;
  ptQTask[74].tQTaskRefList.ptMiddle = nullptr;
  if ( ptNext )
  {
    if ( ptNext[1].tQTaskChildren.ptTail )
    {
      ptNext[2].ptParent = (struct QTask_s *)1;
      ptNext[1].tQTaskChildren.ptTail = nullptr;
    }
    HumanSoldier_CreateGunPickups((struct HumanSoldier_t *)ptQTask);
  }
  v3 = AIDetection_ptDetectionQTaskList;
  if ( QTaskList_IsQTaskRegistered(AIDetection_ptDetectionQTaskList, &igi2_frame.piTask, ptQTask) == false )
    QTaskList_Register(v3, (struct QTaskList_s *)ptQTask);
  v4 = *(float *)&ptQTask[50].tQTaskRefList.ptTail;
  p_tQTaskRefList = &ptQTask[50].tQTaskRefList;
  v6 = *(float *)&ptQTask[50].tQTaskRefList.ptMiddle;
  v7 = *(float *)&ptQTask[50].tQTaskRefList.ptHead;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptHead = ptQTask[29].tQTaskChildren.ptHead;
  v9 = sqrt(v7 * v7 + v6 * v6 + v4 * v4);
  if ( v9 <= 0.0 )
  {
    p_tQTaskRefList->ptHead = nullptr;
    ptQTask[50].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[50].tQTaskRefList.ptTail = nullptr;
  }
  else
  {
    *(float *)&p_tQTaskRefList->ptHead = 1.0 / v9 * *(float *)&p_tQTaskRefList->ptHead;
    *(float *)&ptQTask[50].tQTaskRefList.ptMiddle = 1.0 / v9 * *(float *)&ptQTask[50].tQTaskRefList.ptMiddle;
    *(float *)&ptQTask[50].tQTaskRefList.ptTail = 1.0 / v9 * *(float *)&ptQTask[50].tQTaskRefList.ptTail;
  }
  switch ( (unsigned int)ptQTask[76].ptNext )
  {
    case 0u:
      v14 = Game_ptGame;
      v15 = Game_ptGame->tRunRandomState.anRandom[1];
      v16 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
      Game_ptGame->tRunRandomState.anRandom[2] = v16;
      v17 = v16 ^ v15;
      v18 = v17 + v14->tRunRandomState.anRandom[0];
      v14->tRunRandomState.anRandom[1] = v17;
      v14->tRunRandomState.anRandom[0] = v18;
      v19 = v18;
      v20 = *(float *)&p_tQTaskRefList->ptHead;
      ptTail = ptQTask[50].tQTaskRefList.ptTail;
      igi2_frame.ptMiddle = ptQTask[50].tQTaskRefList.ptMiddle;
      igi2_frame.v36 = *(float *)&ptTail;
      igi2_frame.v34 = v20;
      if ( HumanSoldier_FindCollisionDirectionAndTurn(ptQTask, (struct real32x3_t *)&ptQTask[50].tQTaskRefList) )
        v12 = ((int)(v19 % 0xA) >= 5) + 80;
      else
        v12 = 82;
      igi2_frame.v36 = igi2_frame.v36 * 680.0 + 272.0;
      v22 = *(float *)&igi2_frame.ptMiddle * 680.0;
      *(float *)&ptQTask[38].ptPrev = igi2_frame.v34 * 680.0 + *(float *)&ptQTask[38].ptPrev;
      *(float *)&ptQTask[38].tQTaskChildren.ptHead = v22 + *(float *)&ptQTask[38].tQTaskChildren.ptHead;
      *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = igi2_frame.v36 + *(float *)&ptQTask[38].tQTaskChildren.ptMiddle;
      break;
    case 1u:
      v10 = ptQTask[50].tQTaskRefList.ptMiddle;
      v11 = ptQTask[50].tQTaskRefList.ptTail;
      igi2_frame.v34 = *(float *)&p_tQTaskRefList->ptHead;
      igi2_frame.ptMiddle = v10;
      igi2_frame.v36 = *(float *)&v11;
      v12 = HumanSoldier_FindCollisionDirectionAndTurn(ptQTask, (struct real32x3_t *)&ptQTask[50].tQTaskRefList) != false
          ? 81
          : 68;
      igi2_frame.v36 = igi2_frame.v36 * 680.0 + 272.0;
      v13 = *(float *)&igi2_frame.ptMiddle * 680.0;
      *(float *)&ptQTask[38].ptPrev = igi2_frame.v34 * 680.0 + *(float *)&ptQTask[38].ptPrev;
      *(float *)&ptQTask[38].tQTaskChildren.ptHead = v13 + *(float *)&ptQTask[38].tQTaskChildren.ptHead;
      *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = igi2_frame.v36 + *(float *)&ptQTask[38].tQTaskChildren.ptMiddle;
      break;
    case 2u:
      if ( ptHead != (struct QTask_s *)16 && ptHead != (struct QTask_s *)13 && ptHead != (struct QTask_s *)12
        || HumanSoldier_FindCollisionDirectionAndTurn(ptQTask, (struct real32x3_t *)&ptQTask[50].tQTaskRefList) == false
        || Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) >= 0.30000001192092896
        || *(float *)&ptQTask[76].ptPrev <= 2.0 )
      {
        goto LABEL_23;
      }
      v23 = ptQTask[50].tQTaskRefList.ptMiddle;
      v24 = ptQTask[50].tQTaskRefList.ptTail;
      igi2_frame.v34 = *(float *)&p_tQTaskRefList->ptHead;
      igi2_frame.ptMiddle = v23;
      igi2_frame.v36 = *(float *)&v24;
      v12 = 64;
      igi2_frame.v36 = igi2_frame.v36 * 1088.0 + 544.0;
      *(float *)&ptQTask[38].ptPrev = igi2_frame.v34 * 1088.0 + *(float *)&ptQTask[38].ptPrev;
      *(float *)&ptQTask[38].tQTaskChildren.ptHead = *(float *)&v23 * 1088.0
                                                   + *(float *)&ptQTask[38].tQTaskChildren.ptHead;
      *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = igi2_frame.v36 + *(float *)&ptQTask[38].tQTaskChildren.ptMiddle;
      break;
    case 3u:
    case 4u:
LABEL_23:
      igi2_frame.v37[0] = 65;
      igi2_frame.v37[1] = 66;
      igi2_frame.v37[2] = 67;
      igi2_frame.v37[3] = 71;
      igi2_frame.v37[4] = 72;
      igi2_frame.v37[5] = 73;
      igi2_frame.v37[6] = 74;
      igi2_frame.v37[7] = 75;
      igi2_frame.v37[8] = 76;
      igi2_frame.v37[9] = 77;
      igi2_frame.v37[10] = 78;
      if ( ptHead == (struct QTask_s *)16 )
      {
        v25 = HumanSoldier_iDeathAnimCycle;
        v12 = igi2_frame.v37[HumanSoldier_iDeathAnimCycle % 3];
      }
      else
      {
        v26 = *(float *)&p_tQTaskRefList->ptHead;
        v27 = ptQTask[50].tQTaskRefList.ptTail;
        igi2_frame.ptMiddle = ptQTask[50].tQTaskRefList.ptMiddle;
        v28 = ptQTask[76].ptNext;
        igi2_frame.v34 = v26;
        igi2_frame.v36 = *(float *)&v27;
        if ( v28 == (struct QTask_s *)2 )
        {
          v29 = igi2_frame.v34 * 340.0;
          v30 = *(float *)&igi2_frame.ptMiddle * 340.0;
          igi2_frame.v36 = igi2_frame.v36 * 340.0 + 136.0;
        }
        else if ( v28 == (struct QTask_s *)3 )
        {
          v29 = igi2_frame.v34 * 204.0;
          v30 = *(float *)&igi2_frame.ptMiddle * 204.0;
          igi2_frame.v36 = igi2_frame.v36 * 204.0 + 136.0;
        }
        else
        {
          v29 = 0.0;
          igi2_frame.v36 = 0.0;
          v30 = 0.0;
        }
        v25 = HumanSoldier_iDeathAnimCycle;
        v12 = igi2_frame.v37[HumanSoldier_iDeathAnimCycle];
        *(float *)&ptQTask[38].ptPrev = v29 + *(float *)&ptQTask[38].ptPrev;
        *(float *)&ptQTask[38].tQTaskChildren.ptHead = v30 + *(float *)&ptQTask[38].tQTaskChildren.ptHead;
        *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = igi2_frame.v36 + *(float *)&ptQTask[38].tQTaskChildren.ptMiddle;
      }
      HumanSoldier_iDeathAnimCycle = (v25 + 1) % 11;
      break;
    default:
      v12 = igi2_frame.piTask;
      break;
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, v12, 0, 0.0);
  v31 = ptQTask[34].tQTaskChildren.ptTail;
  if ( v31 )
    v31[1].ptPrev = (struct QTask_s *)((int)v31[1].ptPrev & ~1u);
  v32 = ptQTask[33].tQTaskChildren.ptTail;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(v32[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptQTask[74].ptParent = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)1174405120;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[34].tQTaskChildren.ptTail[1].ptPrev = (struct QTask_s *)((int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev
                                                                 | 0x40);
  ptState->pfState = HumanSoldier_RunStateDie;
}

// source: j/0/human/soldiertypes/humansoldier.c:4493  [anchor-mhash]
void __cdecl HumanSoldier_InitStateKneelDie(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int piTask; };
    struct { char igi2_o1[4]; int aiKneelDieState[6]; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskList_s *v2; // ebx
  struct QTask_s *ptNext; // eax
  struct Game_s *v4; // eax
  unsigned int v5; // ebx
  int v6; // ecx
  int v7; // ecx
  unsigned int v8; // edx
  struct QTask_s *ptTail; // edx
  struct QTask_s *v10; // ecx

  v2 = AIDetection_ptDetectionQTaskList;
  igi2_frame.aiKneelDieState[0] = 55;
  igi2_frame.aiKneelDieState[1] = 56;
  igi2_frame.aiKneelDieState[2] = 57;
  igi2_frame.aiKneelDieState[3] = 58;
  igi2_frame.aiKneelDieState[4] = 59;
  igi2_frame.aiKneelDieState[5] = 60;
  if ( QTaskList_IsQTaskRegistered(AIDetection_ptDetectionQTaskList, &igi2_frame.piTask, ptQTask) == false )
    QTaskList_Register(v2, (struct QTaskList_s *)ptQTask);
  ptNext = ptQTask[33].ptNext;
  ptQTask[74].tQTaskRefList.ptMiddle = nullptr;
  if ( ptNext )
  {
    ptNext[2].ptParent = (struct QTask_s *)1;
    ptNext[1].tQTaskChildren.ptTail = nullptr;
    HumanSoldier_CreateGunPickups((struct HumanSoldier_t *)ptQTask);
  }
  v4 = Game_ptGame;
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  v5 = v4->tRunRandomState.anRandom[1];
  v6 = (v4->tRunRandomState.anRandom[0] >> 7) ^ v4->tRunRandomState.anRandom[2];
  v4->tRunRandomState.anRandom[2] = v6;
  v7 = v6 ^ v5;
  v8 = v7 + v4->tRunRandomState.anRandom[0];
  v4->tRunRandomState.anRandom[1] = v7;
  v4->tRunRandomState.anRandom[0] = v8;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, igi2_frame.aiKneelDieState[v8 % 6], 0, 0.0);
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 1;
  v10 = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
  ptQTask[74].ptParent = v10;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)1174405120;
  ptQTask[34].tQTaskChildren.ptTail[1].ptPrev = (struct QTask_s *)((int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev
                                                                 | 0x40);
  ptState->pfState = HumanSoldier_RunStateDie;
}

// source: j/0/human/soldiertypes/humansoldier.c:4557  [anchor-mhash]
void __cdecl HumanSoldier_InitStateLieDownDie(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTaskList_s *v2; // ebx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptTail; // eax
  int piTask; // [esp+Ch] [ebp-4h] BYREF

  v2 = AIDetection_ptDetectionQTaskList;
  if ( QTaskList_IsQTaskRegistered(AIDetection_ptDetectionQTaskList, &piTask, ptQTask) == false )
    QTaskList_Register(v2, (struct QTaskList_s *)ptQTask);
  ptNext = ptQTask[33].ptNext;
  ptQTask[74].tQTaskRefList.ptMiddle = nullptr;
  if ( ptNext )
  {
    ptNext[2].ptParent = (struct QTask_s *)1;
    ptNext[1].tQTaskChildren.ptTail = nullptr;
    HumanSoldier_CreateGunPickups((struct HumanSoldier_t *)ptQTask);
  }
  *(_DWORD *)&ptQTask[32].eQTaskType = 2;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 43, 0, 0.0);
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
  ptState->pfState = HumanSoldier_RunStateDie;
  ptQTask[49].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:4609  [anchor-mhash]
void __cdecl HumanSoldier_InitStateDead(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTaskList_s *v2; // ebx
  struct QTask_s *v3; // esi
  int ptTail; // ebx
  struct QTask_s *v5; // ecx

  v2 = AIDetection_ptDetectionQTaskList;
  v3 = ptQTask;
  if ( QTaskList_IsQTaskRegistered(AIDetection_ptDetectionQTaskList, (int *)&ptQTask, ptQTask) == false )
    QTaskList_Register(v2, (struct QTaskList_s *)v3);
  ptTail = (int)v3[35].tQTaskChildren.ptTail;
  *(_DWORD *)&v3[32].eQTaskType = 0;
  HumanAnim_SetAnimationAtEndFromState(v3, ptTail, 0.0);
  v5 = v3[33].tQTaskChildren.ptTail;
  v3[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(v5[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(v3[34].tQTaskChildren.ptMiddle) = 1;
  LOBYTE(v3[36].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(v3[36].tQTaskChildren.ptTail) = 0;
  ptState->pfState = HumanSoldier_RunStateDie;
}

// source: j/0/human/soldiertypes/humansoldier.c:4652  [anchor-mhash]
void __cdecl HumanSoldier_RunStateDie(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  struct HumanAIEventContext_t tLocalEventContext; // [esp+8h] [ebp-44h] BYREF

  bSignal = ptState->bSignal;
  ptQTask[76].tQTaskChildren.ptHead = (struct QTask_s *)1;
  if ( (bSignal & 1) != 0 )
  {
    tLocalEventContext.ptHumanOriginatorQTask = ptQTask;
    ptState->pfState = HumanSoldier_RunStateDie2;
    tLocalEventContext.eEvent = 10;
    tLocalEventContext.eTeam = -1;
    tLocalEventContext.bFlags = 1090;
    tLocalEventContext.ptReferenceQTask = nullptr;
    tLocalEventContext.ptPosition = (struct real64x3_t *)&ptQTask[1];
    tLocalEventContext.vRadius = 20480.0;
    HumanAI_SendEvent(&tLocalEventContext);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:4687  [anchor-mhash]
void __cdecl HumanSoldier_RunStateDie2(struct State_s *ptState, struct QTask_s *ptQTask)
{
  char v2; // dl

  v2 = BYTE2(ptQTask[50].ptNext);
  *(_DWORD *)&ptQTask[32].eQTaskType = 2;
  LOBYTE(ptQTask[32].tQTaskRefList.ptTail) = 1;
  if ( v2 )
    ptQTask[76].tQTaskChildren.ptHead = (struct QTask_s *)2;
}

// source: j/0/human/soldiertypes/humansoldier.c:4712  [anchor-mhash]
void __cdecl HumanSoldier_InitStateStandAction(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct WeaponType_s *ptWeaponType; };
    struct { char igi2_o1[4]; char *zName; };
    struct { char igi2_o2[8]; unsigned __int8 *ptHierarchy; };
    struct { char igi2_o3[12]; char zFullAnimName[256]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // edx
  struct QTask_s *ptParent; // esi
  struct QTask_s *v4; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptMiddle; // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v14; // eax
  char *v15; // ebp
  char v16; // cl
  _WORD *v17; // edi
  char v18; // al
  unsigned int v19; // eax
  char *v20; // edi
  unsigned __int8 *v22; // esi
  struct AnimHeader_s *Anim; // eax
  char *v24; // eax
  char v25; // cl
  _WORD *v26; // edi
  char v27; // al
  enum WeaponType_e eWeaponType; // eax
  __int32 v29; // eax
  _DWORD *v30; // edi
  char v31; // al
  char *v32; // edi
  char *v34; // edi
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *v39; // edi

  ptNext = ptQTask[33].ptNext;
  ptParent = ptQTask[48].ptParent;
  if ( ptNext
    && (v4 = ptNext[1].ptPrev) != nullptr
    && (ptTail = v4->tQTaskChildren.ptTail) != nullptr
    && (ptQTask[7].tQTaskRefList.ptTail != *(struct QReference_s **)&ptTail[48].tQTaskChildren.ptHead[24].eQTaskType
      ? (ptMiddle = ptTail[48].tQTaskChildren.ptMiddle)
      : (ptMiddle = ptTail[48].tQTaskChildren.ptHead),
        ptMiddle) )
  {
    igi2_frame.ptHierarchy = *(unsigned __int8 **)&ptMiddle[24].eQTaskType;
    if ( igi2_frame.ptHierarchy )
    {
      ptPrev = ptNext[1].ptPrev;
      if ( ptPrev )
        igi2_frame.ptWeaponType = (struct WeaponType_s *)ptPrev->tQTaskChildren.ptTail;
      else
        igi2_frame.ptWeaponType = nullptr;
      v14 = ptParent + 1;
      igi2_frame.zName = (char *)&ptParent[1];
      v15 = (char *)(igi2_frame.zFullAnimName - (char *)&ptParent[1]);
      do
      {
        v16 = (char)v14->ptNext;
        v15[(_DWORD)v14] = (char)v14->ptNext;
        v14 = (struct QTask_s *)((char *)v14 + 1);
      }
      while ( v16 );
      v17 = (_WORD *)((char *)&igi2_frame.ptHierarchy + 3);
      do
      {
        v18 = *((_BYTE *)v17 + 1);
        v17 = (_WORD *)((char *)v17 + 1);
      }
      while ( v18 );
      *v17 = 95;
      v19 = strlen(igi2_frame.ptWeaponType->zAnimName) + 1;
      v20 = (char *)&igi2_frame.ptHierarchy + 3;
      while ( *++v20 )
        ;
      qmemcpy(v20, igi2_frame.ptWeaponType->zAnimName, v19);
      v22 = igi2_frame.ptHierarchy;
      Anim = Hierarchy_GetAnim(igi2_frame.ptHierarchy, igi2_frame.zFullAnimName);
      if ( Anim )
        goto LABEL_46;
      v24 = igi2_frame.zName;
      do
      {
        v25 = *v24;
        v15[(_DWORD)v24] = *v24;
        ++v24;
      }
      while ( v25 );
      v26 = (_WORD *)((char *)&igi2_frame.ptHierarchy + 3);
      do
      {
        v27 = *((_BYTE *)v26 + 1);
        v26 = (_WORD *)((char *)v26 + 1);
      }
      while ( v27 );
      *v26 = 95;
      eWeaponType = igi2_frame.ptWeaponType->eWeaponType;
      if ( eWeaponType )
      {
        v29 = eWeaponType - 1;
        if ( v29 )
        {
          if ( v29 == 1 )
          {
            v30 = (unsigned __int8 **)((char *)&igi2_frame.ptHierarchy + 3);
            do
            {
              v31 = *((_BYTE *)v30 + 1);
              v30 = (_DWORD *)((char *)v30 + 1);
            }
            while ( v31 );
            *v30 = 1953458291;
            v30[1] = &QTask_aaisHandlerSetDirectly[158351];
          }
        }
        else
        {
          v32 = (char *)&igi2_frame.ptHierarchy + 3;
          while ( *++v32 )
            ;
          strcpy(v32, "pistol");
        }
      }
      else
      {
        v34 = (char *)&igi2_frame.ptHierarchy + 3;
        while ( *++v34 )
          ;
        strcpy(v34, "rifle");
      }
      Anim = Hierarchy_GetAnim(v22, igi2_frame.zFullAnimName);
      if ( Anim || (Anim = Hierarchy_GetAnim(v22, igi2_frame.zName)) != nullptr )
      {
LABEL_46:
        HumanAnim_SetAnimation(ptQTask, Anim, 0, 0.5);
        v39 = ptQTask[74].ptParent;
        LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
        ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)v39 | 1);
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
        ptState->pfState = HumanSoldier_RunStateStandAction;
        ptQTask[36].ptPrev = nullptr;
        ptQTask[36].tQTaskChildren.ptHead = nullptr;
        ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
        LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
      }
      else
      {
        v36 = ptState->apfExitState[ptState->nState];
        if ( v36 )
          v36(ptState, ptQTask);
        apfState = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v38 = *apfState;
        ptState->pfState = *apfState;
        v38(ptState, ptQTask);
      }
    }
    else
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, ptQTask);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v12 = *v11;
      ptState->pfState = *v11;
      v12(ptState, ptQTask);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, ptQTask);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v9 = *v8;
    ptState->pfState = v9;
    v9(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:4803  [anchor-mhash]
void __cdecl HumanSoldier_RunStateStandAction(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // ebx
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  double v12; // st7
  struct QTask_s *ptNext; // ecx
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptPrev; // edx
  struct QTask_s *ptMiddle; // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  struct real64x3_t tReal64x3; // [esp+18h] [ebp-18h] BYREF

  bSignal = ptState->bSignal;
  if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v8 = apfState[41];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( (bSignal & 0x20000) != 0 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 71;
      v11 = v10[71];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( (bSignal & 0x10003E1) != 0 )
    {
      v12 = *(float *)&ptQTask[7].tQTaskRefList.ptMiddle + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
      ptNext = ptQTask[1].ptNext;
      LODWORD(tReal64x3.vY) = ptQTask[1].tQTaskChildren.ptHead;
      tReal64x3.vZ = v12;
      ptParent = ptQTask[74].ptParent;
      ptPrev = ptQTask[1].ptPrev;
      LODWORD(tReal64x3.vX) = ptNext;
      ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
      LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
      HIDWORD(tReal64x3.vX) = ptPrev;
      HIDWORD(tReal64x3.vY) = ptMiddle;
      if ( ((unsigned __int8)ptParent & 1) != 0 )
      {
        ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      }
      Human_PopPosition(ptQTask, &tReal64x3);
      if ( (bSignal & 1) != 0 && BYTE1(ptQTask[75].ptPrev) )
      {
        v17 = ptState->apfExitState[ptState->nState];
        if ( v17 )
          v17(ptState, ptQTask);
        v18 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 84;
        v19 = v18[84];
        ptState->pfState = v19;
        v19(ptState, ptQTask);
      }
      else
      {
        v20 = ptState->apfExitState[ptState->nState];
        if ( v20 )
          v20(ptState, ptQTask);
        v21 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v22 = *v21;
        ptState->pfState = *v21;
        v22(ptState, ptQTask);
      }
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    v4 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 39;
    v5 = v4[39];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:4857  [anchor-mhash]
void __cdecl HumanSoldier_InitStateStationaryGun(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char isAttachedOnHeli; };
    struct { char igi2_o1[1]; struct QTask_s *ptAttachQTask; };
    struct { char igi2_o2[5]; float vGamma; };
    struct { char igi2_o3[9]; float vBeta; };
    struct { char igi2_o4[13]; float vAlpha; };
    struct { char igi2_o5[17]; struct real64x3_t tPos; };
    struct { char igi2_o6[41]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o7[65]; struct real32x9_t tOrientation; };
    char igi2_extent[105];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *ptParent; // eax
  int v4; // esi
  int ptTail; // edi
  int GraphNodeDataSize; // eax
  int v7; // eax
  double v8; // st7
  double v9; // st6
  struct QTask_s *v10; // edi
  struct QTask_s *v11; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  igi2_frame.ptAttachQTask = nullptr;
  if ( ptHead )
    igi2_frame.ptAttachQTask = (struct QTask_s *)ptHead->pxObject;
  ptParent = ptQTask[48].ptParent;
  v4 = (int)ptParent[728].tQTaskChildren.ptHead;
  ptTail = (int)ptParent[748].tQTaskRefList.ptTail;
  igi2_frame.isAttachedOnHeli = 0;
  if ( *(_DWORD *)(v4 + 132) && ptTail < (int)(*(_DWORD *)(v4 + 104)) && ptTail >= 0 )
  {
    GraphNodeDataSize = Graph_GetGraphNodeDataSize(v4);
    v7 = *(_DWORD *)(*(_DWORD *)(v4 + 132) + ptTail * GraphNodeDataSize) == -1
       ? 0
       : ptTail * GraphNodeDataSize + *(_DWORD *)(v4 + 132);
  }
  else
  {
    v7 = 0;
  }
  if ( (AIGraph_bVehicleNodeCriteria & *(_DWORD *)(v7 + 56)) != 0 )
    igi2_frame.isAttachedOnHeli = 1;
  qmemcpy(&igi2_frame.tOrientation, &igi2_frame.ptAttachQTask[3].ptPrev, sizeof(igi2_frame.tOrientation));
  GameFunctions_GetMagicVertex(&igi2_frame.tPos, igi2_frame.ptAttachQTask, 0);
  v8 = -204.8;
  v9 = -6348.8;
  if ( igi2_frame.isAttachedOnHeli )
  {
    v8 = -3686.4;
    v9 = -3891.2;
  }
  v10 = ptQTask;
  igi2_frame.Real64x3_Rotate_tTemp.vX = igi2_frame.tOrientation.tX.vZ * v9 + igi2_frame.tOrientation.tX.vY * v8 + igi2_frame.tOrientation.tX.vX * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.tOrientation.tY.vZ * v9 + igi2_frame.tOrientation.tY.vY * v8 + igi2_frame.tOrientation.tY.vX * 0.0;
  igi2_frame.tPos.vX = igi2_frame.tPos.vX + igi2_frame.Real64x3_Rotate_tTemp.vX;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY + igi2_frame.Real64x3_Rotate_tTemp.vY;
  igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + igi2_frame.tOrientation.tZ.vZ * v9 + igi2_frame.tOrientation.tZ.vY * v8 + igi2_frame.tOrientation.tZ.vX * 0.0;
  Human_PopPosition(ptQTask, &igi2_frame.tPos);
  Real32x9_GetAngles(&igi2_frame.tOrientation, &igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
  Human_PopOrientation(ptQTask, igi2_frame.vGamma);
  if ( igi2_frame.isAttachedOnHeli )
  {
    *(_DWORD *)&ptQTask[32].eQTaskType = 1;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 28, 0, 0.0);
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 85, 0, 0.0);
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
  }
  else
  {
    ptQTask[74].ptParent = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 85, 0, 0.0);
    v10 = ptQTask;
  }
  v11 = v10[33].tQTaskChildren.ptTail;
  *(_DWORD *)&v11[11].eQTaskType = 0;
  v11[12].ptNext = nullptr;
  v11[12].ptPrev = nullptr;
  v11[12].tQTaskRefList.ptHead = nullptr;
  v11[12].tQTaskChildren.ptHead = nullptr;
  v11[12].tQTaskChildren.ptMiddle = nullptr;
  v11[12].tQTaskChildren.ptTail = nullptr;
  v11[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(v10[34].tQTaskChildren.ptMiddle) = 1;
  Human_AttachToTask(v10, igi2_frame.ptAttachQTask, &igi2_frame.tPos, &igi2_frame.tOrientation);
  ptState->pfState = HumanSoldier_RunStateStationaryGun;
  LOBYTE(v10[36].tQTaskChildren.ptTail) = 1;
  v10[36].ptPrev = nullptr;
  v10[36].tQTaskChildren.ptHead = nullptr;
  v10[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:4948  [anchor-mhash]
void __cdecl HumanSoldier_RunStateStationaryGun(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax

  if ( (ptState->bSignal & 0x220000) != 0 )
  {
    HumanSoldier_DeactivateStationaryGun(ptQTask);
    ptQTask[34].tQTaskChildren.ptTail[1].ptPrev = (struct QTask_s *)((int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev
                                                                   & ~0x40u);
    ptParent = ptQTask[74].ptParent;
    LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
    if ( ((unsigned __int8)ptParent & 1) != 0 )
    {
      ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    }
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v5 = *apfState;
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:4988  [anchor-mhash]
void __cdecl HumanSoldier_DeactivateStationaryGun(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // ecx
  struct QTask_s *pxObject; // eax
  struct QReference_s *v3; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (struct QTask_s *)ptHead->pxObject;
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  StationaryGun_Deactivate(pxObject);
  v3 = ptQTask[46].tQTaskRefList.ptHead;
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  if ( v3 )
  {
    QReference_Delete(v3, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  ptQTask[44].tQTaskRefList.ptTail = nullptr;
  ptQTask[48].ptNext = nullptr;
  *(_DWORD *)&ptQTask[47].eQTaskType = 1;
}

// source: j/0/human/soldiertypes/humansoldier.c:5025  [anchor-mhash]
void __cdecl HumanSoldier_InitStateDoor(struct State_s *ptState, struct QTask_s *ptQTask)
{
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptState->pfState = HumanSoldier_RunStateDoor;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
}

// source: j/0/human/soldiertypes/humansoldier.c:5039  [anchor-mhash]
void __cdecl HumanSoldier_RunStateDoor(struct State_s *ptState, struct QTask_s *ptQTask)
{
  void (__cdecl *v2)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax

  if ( (ptState->bSignal & 1) != 0 )
  {
    v2 = ptState->apfExitState[ptState->nState];
    if ( v2 )
      v2(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v4 = *apfState;
    ptState->pfState = v4;
    v4(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5064  [anchor-mhash]
void __cdecl HumanSoldier_InitStateStandPressSwitch(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *v2; // ebx

  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  v2 = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
  ptQTask[74].ptParent = v2;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptState->pfState = HumanSoldier_RunStateStandPressSwitch;
}

// source: j/0/human/soldiertypes/humansoldier.c:5084  [anchor-mhash]
void __cdecl HumanSoldier_RunStateStandPressSwitch(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax

  if ( (ptState->bSignal & 1) != 0 )
  {
    ptParent = ptQTask[74].ptParent;
    if ( ((unsigned __int8)ptParent & 1) != 0 )
    {
      ptQTask[74].ptParent = (struct QTask_s *)((unsigned int)ptParent & 0xFFFFFFFE);
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    }
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v5 = *apfState;
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5113  [anchor-mhash]
void __cdecl HumanSoldier_InitStateSilentKill(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  int piTask; // [esp+Ch] [ebp-4h] BYREF

  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 40, 0, 0.0);
  ptQTask[25].tQTaskRefList.ptHead = ptQTask[25].tQTaskRefList.ptMiddle;
  ptNext = ptQTask[33].ptNext;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
  ptQTask[50].tQTaskChildren.ptHead = nullptr;
  ptQTask[50].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[50].tQTaskChildren.ptTail = nullptr;
  ptQTask[76].tQTaskChildren.ptHead = (struct QTask_s *)2;
  BYTE2(ptQTask[50].ptNext) = 1;
  ptQTask[48].ptPrev = (struct QTask_s *)1;
  LOBYTE(ptQTask[29].tQTaskRefList.ptHead) = 1;
  if ( ptNext )
  {
    if ( ptNext[1].tQTaskChildren.ptTail )
    {
      ptNext[2].ptParent = (struct QTask_s *)1;
      ptNext[1].tQTaskChildren.ptTail = nullptr;
    }
    HumanSoldier_CreateGunPickups((struct HumanSoldier_t *)ptQTask);
  }
  if ( QTaskList_IsQTaskRegistered(AIDetection_ptDetectionQTaskList, &piTask, ptQTask) == false )
    QTaskList_Register(AIDetection_ptDetectionQTaskList, (struct QTaskList_s *)ptQTask);
  ptQTask[74].ptParent = (struct QTask_s *)((int)ptQTask[74].ptParent | 1);
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptState->pfState = HumanSoldier_RunStateSilentKill;
}

// source: j/0/human/soldiertypes/humansoldier.c:5165  [anchor-mhash]
void __cdecl HumanSoldier_RunStateSilentKill(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle > 9600 )
    BYTE2(ptQTask[50].ptNext) = 0;
  if ( (bSignal & 1) != 0 )
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 101;
    v5 = apfState[101];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5200  [size]
void __cdecl HumanSoldier_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanSoldier_ptSerializeParameterList;
}

// source: j/0/human/soldiertypes/humansoldier.c:5222  [anchor-mhash]
void __cdecl HumanSoldier_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptHead; // eax
  _WORD *pxObject; // eax
  int v4; // ecx
  long double v5; // st7
  long double v6; // st7
  long double v7; // st6
  struct QTask_s *ptNext; // eax
  struct QTask_s *v9; // eax
  struct QTask_s *v10; // edx
  struct QTask_s *v11; // ecx
  struct QTask_s *v12; // ebx
  struct QTask_s *v13; // ecx
  int v14; // edx
  struct QTask_s *v15; // edx
  struct TexInfo_s *p_tTexInfo; // ecx
  struct QReference_s *v17; // eax
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *v19; // eax
  struct QTask_s *v20; // eax
  int v21; // eax
  struct QTask_s *v22; // edx
  struct QTask_s *v23; // eax
  void (__cdecl *v24)(struct QReference_s **, struct QTask_s *); // eax
  struct QTask_s **v25; // edx
  struct QTask_s *v26; // eax
  struct QTask_s *v27; // ebx
  struct GameTexture_s *v28; // ecx
  struct QTask_s *v29; // ecx
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptPrev; // edx
  struct QTask_s *ptParent; // ecx
  void (__cdecl *v33)(struct QReference_s **, struct QTask_s *); // ecx
  struct QReference_s *v34; // eax
  struct QTask_s *v35; // eax
  struct HumanAI_s *ptHumanAI; // [esp+Ch] [ebp-Ch]
  long double v37; // [esp+10h] [ebp-8h]

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    pxObject = ptHead->pxObject;
    if ( pxObject )
    {
      if ( QTask_IsQTaskTypeDerived(pxObject[18], StationaryGun_eQTaskType) )
        HumanSoldier_DeactivateStationaryGun(ptQTask);
    }
  }
  ptHumanAI = (struct HumanAI_s *)ptQTask[48].ptParent;
  v4 = Human_eQTaskType + 511 * Serialize_eDeSerializeQTaskEvent;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[34].ptPrev = nullptr;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v4].pfHandler)(ptQTask, pxContext);
  v5 = *(float *)&ptQTask[34].ptPrev;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  v37 = v5;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  v6 = sin(v5);
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[4].ptNext = nullptr;
  v7 = cos(v37);
  *(float *)&ptQTask[3].ptPrev = v7;
  *(float *)&ptQTask[3].tQTaskChildren.ptHead = -v6;
  *(float *)&ptQTask[3].tQTaskChildren.ptTail = v6;
  *(float *)&ptQTask[3].tQTaskRefList.ptHead = v7;
  ptNext = ptQTask[33].ptNext;
  if ( ptNext[1].tQTaskChildren.ptTail )
  {
    ptNext[2].ptParent = (struct QTask_s *)1;
    ptNext[1].tQTaskChildren.ptTail = nullptr;
    v9 = ptQTask[33].ptNext;
    v9[3].tQTaskRefList.ptHead = (struct QReference_s *)1;
    v9[1].tQTaskChildren.ptTail = nullptr;
  }
  Weapon_StopAllSound(ptQTask[33].ptNext);
  v10 = ptQTask[33].ptNext;
  LOBYTE(ptQTask[75].ptPrev) = 0;
  ptQTask[74].ptParent = nullptr;
  ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
  ptQTask[75].tQTaskChildren.ptMiddle = nullptr;
  v11 = v10[5].ptNext;
  if ( v11 && v11->tQTaskChildren.ptHead )
  {
    v12 = v11->tQTaskChildren.ptHead;
    v13 = v12 + 6;
    v14 = 15;
    do
    {
      v13->ptNext = nullptr;
      v13 = (struct QTask_s *)((char *)v13 + 72);
      --v14;
    }
    while ( v14 );
    v12[4].ptPrev = nullptr;
  }
  if ( LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
  {
    v27 = ptQTask[47].ptNext;
    v28 = Human_ptBloodPuddle;
    HIBYTE(ptQTask[50].ptNext) = 1;
    v27[3].tQTaskChildren.ptMiddle = (struct QTask_s *)&v28->tTexInfo;
    v29 = ptQTask[47].ptNext;
    v29[2].ptNext = ptQTask[49].ptParent;
    v29[7].ptParent = (struct QTask_s *)1;
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
    LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
    LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
    ptQTask[50].tQTaskChildren.ptHead = nullptr;
    ptQTask[50].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[50].tQTaskChildren.ptTail = nullptr;
    ptTail[1].ptPrev = (struct QTask_s *)((int)ptTail[1].ptPrev | 0x40);
    ptQTask[76].tQTaskChildren.ptHead = (struct QTask_s *)2;
    HIBYTE(ptHumanAI->avChannel[5]) = 1;
    BYTE2(ptQTask[50].ptNext) = 1;
    ptPrev = ptQTask[31].ptPrev;
    ptParent = ptQTask[30].ptParent;
    ptQTask[31].tQTaskChildren.ptHead = (struct QTask_s *)HumanSoldier_InitStateDead;
    v33 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptParent->ptNext + (_DWORD)ptPrev);
    if ( v33 )
      v33(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v34 = ptQTask[30].tQTaskRefList.ptTail;
    ptQTask[31].ptNext = ptQTask[31].ptPrev;
    ptQTask[31].ptPrev = (struct QTask_s *)101;
    v35 = (struct QTask_s *)v34[33].pxObject;
    ptQTask[31].tQTaskChildren.ptHead = v35;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v35)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  }
  else
  {
    v15 = ptQTask[47].ptNext;
    p_tTexInfo = &Human_ptShadow->tTexInfo;
    HIBYTE(ptQTask[50].ptNext) = 0;
    v15[3].tQTaskChildren.ptMiddle = (struct QTask_s *)p_tTexInfo;
    BoneDynCubeObj_DeInitBloodStains((struct BoneDynCubeObj_s *)ptQTask);
    BoneDynCubeObj_InitBloodStains((struct BoneDynCubeObj_s *)ptQTask);
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 0, 0, 0.0);
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
    LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
    ptQTask[50].tQTaskChildren.ptHead = nullptr;
    ptQTask[50].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[50].tQTaskChildren.ptTail = nullptr;
    BYTE2(ptQTask[50].ptNext) = 0;
    ptQTask[76].tQTaskChildren.ptHead = nullptr;
    HIBYTE(ptHumanAI->avChannel[5]) = 0;
    ptQTask[34].tQTaskChildren.ptTail[1].ptPrev = (struct QTask_s *)((int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev
                                                                   & ~0x40u);
    v17 = ptQTask[34].tQTaskRefList.ptHead;
    if ( v17 )
      v17[3].pxObject = (void *)((int)v17[3].pxObject & ~0x40u);
    ptMiddle = ptQTask[34].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
      ptMiddle[3].pxObject = (void *)((int)ptMiddle[3].pxObject & ~0x40u);
    v19 = ptQTask[34].tQTaskRefList.ptTail;
    if ( v19 )
      v19[3].pxObject = (void *)((int)v19[3].pxObject & ~0x40u);
    v20 = ptQTask[34].ptParent;
    if ( v20 )
      v20[1].ptPrev = (struct QTask_s *)((int)v20[1].ptPrev & ~0x40u);
    v21 = *(_DWORD *)&ptQTask[34].eQTaskType;
    if ( v21 )
      *(_DWORD *)(v21 + 44) &= ~0x40u;
    AnimController_Step(
      (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
      (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
    + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
    v22 = ptQTask[31].ptPrev;
    v23 = ptQTask[30].ptParent;
    ptQTask[31].tQTaskChildren.ptHead = (struct QTask_s *)HumanSoldier_InitStateStand;
    v24 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&v23->ptNext + (_DWORD)v22);
    if ( v24 )
      v24(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v25 = (struct QTask_s **)ptQTask[30].tQTaskRefList.ptTail;
    ptQTask[31].ptNext = ptQTask[31].ptPrev;
    ptQTask[31].ptPrev = nullptr;
    v26 = *v25;
    ptQTask[31].tQTaskChildren.ptHead = *v25;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v26)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5346  [size]
void __cdecl HumanSoldier_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[Serialize_eSerializeQTaskEvent][Human_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/human/soldiertypes/humansoldier.c:5362  [anchor-strings]
void __cdecl HumanSoldier_TriggerAnimTriggerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx

  v2 = *(_DWORD *)pxContext;
  if ( QTask_IsQTaskTypeDerived(*(_WORD *)(*(_DWORD *)pxContext + 36), HumanSoldier_eQTaskType) )
  {
    if ( *((_DWORD *)pxContext + 2) == 11 )
    {
      *(_DWORD *)(v2 + 1236) |= 0x8000000u;
    }
    else
    {
      if ( *((_DWORD *)pxContext + 2) != 12 )
      {
        LDebug_Error("Unknown animtrigger for humansoldier: %d", *((_DWORD *)pxContext + 2));
        abort();
      }
      *(_DWORD *)(v2 + 1236) |= 0x10000000u;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5409  [size]
void __cdecl HumanSoldier_ParentChangedQTaskEvent(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[4][Human_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/human/soldiertypes/humansoldier.c:5435  [anchor-mhash]
void __cdecl HumanSoldier_WeaponGetParentParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tDelta; };
    struct { char igi2_o1[4]; float tDelta_4; };
    struct { char igi2_o2[4]; float tDelta_4a; };
    struct { char igi2_o3[12]; float tTemp_; };
    struct { char igi2_o4[16]; float tTemp__4; };
    struct { char igi2_o5[20]; float tTemp__8; };
    struct { char igi2_o6[24]; struct real64x3_t tReal64x3; };
    struct { char igi2_o7[48]; struct real32x9_t tReal32x9; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *ptParent; // edx
  struct Game_s *v3; // eax
  unsigned int v4; // ecx
  unsigned int v5; // edi
  int v6; // edi
  unsigned int v7; // esi
  unsigned int v8; // edi
  int v9; // edi
  unsigned int v10; // esi
  int v11; // edi
  int v12; // edi
  double v13; // st7
  double v14; // st6
  int v15; // ebx
  long double v16; // st2
  long double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st6
  long double v21; // st4
  long double v22; // st7
  struct real32x9_t *p_tReal32x9; // esi

  ptParent = (double *)ptQTask[48].ptParent;
  v3 = Game_ptGame;
  v4 = Game_ptGame->tRunRandomState.anRandom[0];
  v5 = (v4 >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v5;
  v6 = v5 ^ v3->tRunRandomState.anRandom[1];
  v3->tRunRandomState.anRandom[1] = v6;
  v7 = v4 + v6;
  v3->tRunRandomState.anRandom[0] = v4 + v6;
  v8 = ((v4 + v6) >> 7) ^ v3->tRunRandomState.anRandom[2];
  v3->tRunRandomState.anRandom[2] = v8;
  v9 = v8 ^ v3->tRunRandomState.anRandom[1];
  v3->tRunRandomState.anRandom[1] = v9;
  v10 = v7 + v9;
  v3->tRunRandomState.anRandom[0] = v10;
  v11 = (v10 >> 7) ^ v3->tRunRandomState.anRandom[2];
  v3->tRunRandomState.anRandom[2] = v11;
  v12 = v11 ^ v3->tRunRandomState.anRandom[1];
  v3->tRunRandomState.anRandom[0] = v10 + v12;
  v3->tRunRandomState.anRandom[1] = v12;
  qmemcpy(&igi2_frame.tReal64x3, ptParent + 3750, sizeof(igi2_frame.tReal64x3));
  v13 = igi2_frame.tReal64x3.vX - ptParent[12];
  igi2_frame.tDelta_4 = igi2_frame.tReal64x3.vY - ptParent[13];
  v14 = igi2_frame.tReal64x3.vZ - ptParent[14];
  v15 = 0;
  v16 = sqrt(v13 * v13 + igi2_frame.tDelta_4 * igi2_frame.tDelta_4 + v14 * v14);
  if ( v16 > 0.0 )
  {
    igi2_frame.tDelta = 1.0 / v16 * v13;
    igi2_frame.tDelta_4a = igi2_frame.tDelta_4 * (1.0 / v16);
    v17 = 1.0 / v16 * v14;
    *(float *)&igi2_frame.tReal64x3.vX = igi2_frame.tDelta_4a - 0.0 * v17;
    *((float *)&igi2_frame.tReal64x3.vX + 1) = -(igi2_frame.tDelta - 0.0 * v17);
    v18 = igi2_frame.tDelta * 0.0 - igi2_frame.tDelta_4a * 0.0;
    if ( sqrt(
           *(float *)&igi2_frame.tReal64x3.vX * *(float *)&igi2_frame.tReal64x3.vX
         + *((float *)&igi2_frame.tReal64x3.vX + 1) * *((float *)&igi2_frame.tReal64x3.vX + 1)
         + v18 * v18) > 0.0 )
    {
      igi2_frame.tReal32x9.tZ.vY = v17;
      igi2_frame.tReal32x9.tY.vY = igi2_frame.tDelta_4a;
      igi2_frame.tReal32x9.tZ.vX = v18;
      igi2_frame.tReal32x9.tX.vY = igi2_frame.tDelta;
      igi2_frame.tReal32x9.tY.vX = *((float *)&igi2_frame.tReal64x3.vX + 1);
      igi2_frame.tReal32x9.tX.vX = *(float *)&igi2_frame.tReal64x3.vX;
      igi2_frame.tTemp_ = *((float *)&igi2_frame.tReal64x3.vX + 1) * v17 - v18 * igi2_frame.tDelta_4a;
      igi2_frame.tTemp__4 = -(*(float *)&igi2_frame.tReal64x3.vX * v17 - v18 * igi2_frame.tDelta);
      v19 = *(float *)&igi2_frame.tReal64x3.vX;
      *(float *)&igi2_frame.tReal64x3.vX = igi2_frame.tTemp_;
      v20 = *((float *)&igi2_frame.tReal64x3.vX + 1);
      *((float *)&igi2_frame.tReal64x3.vX + 1) = igi2_frame.tTemp__4;
      igi2_frame.tTemp__8 = v19 * igi2_frame.tDelta_4a - v20 * igi2_frame.tDelta;
      *(float *)&igi2_frame.tReal64x3.vY = igi2_frame.tTemp__8;
      if ( igi2_frame.tTemp_ == 0.0 && igi2_frame.tTemp__4 == 0.0 && igi2_frame.tTemp__8 == 0.0 )
      {
        v22 = *(float *)&igi2_frame.tReal64x3.vY;
      }
      else
      {
        v21 = sqrt(igi2_frame.tTemp_ * igi2_frame.tTemp_ + igi2_frame.tTemp__4 * igi2_frame.tTemp__4 + igi2_frame.tTemp__8 * igi2_frame.tTemp__8);
        *(float *)&igi2_frame.tReal64x3.vX = igi2_frame.tTemp_ * (1.0 / v21);
        *((float *)&igi2_frame.tReal64x3.vX + 1) = *((float *)&igi2_frame.tReal64x3.vX + 1) * (1.0 / v21);
        v22 = 1.0 / v21 * *(float *)&igi2_frame.tReal64x3.vY;
      }
      igi2_frame.tReal32x9.tZ.vZ = v22;
      igi2_frame.tReal32x9.tY.vZ = *((float *)&igi2_frame.tReal64x3.vX + 1);
      igi2_frame.tReal32x9.tX.vZ = *(float *)&igi2_frame.tReal64x3.vX;
      v15 = 1;
    }
  }
  qmemcpy(pxContext, ptParent + 12, 0x18u);
  p_tReal32x9 = &igi2_frame.tReal32x9;
  if ( !v15 )
    p_tReal32x9 = (struct real32x9_t *)(ptParent + 20);
  qmemcpy((char *)pxContext + 24, p_tReal32x9, 0x28u);
}

// source: j/0/human/soldiertypes/humansoldier.c:5510  [anchor-mhash]
void __cdecl HumanSoldier_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t ptPos; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v2; // edx
  double v3; // st7
  double v4; // st6
  double v5; // st5
  struct QTask_s *ptNext; // eax

  memset(&ptQTask[74].tQTaskRefList.ptMiddle, 0, 0x50u);
  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][Human_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v2 = Game_ptGame;
  v3 = *(float *)&ptQTask[7].tQTaskRefList.ptMiddle;
  v4 = *(float *)&ptQTask[7].tQTaskRefList.ptHead;
  v5 = *(float *)&ptQTask[7].tQTaskChildren.ptTail;
  ptQTask[36].tQTaskRefList.ptTail = nullptr;
  ptQTask[36].ptParent = nullptr;
  *(_DWORD *)&ptQTask[36].eQTaskType = 0;
  ptQTask[37].ptNext = nullptr;
  ptQTask[37].ptPrev = nullptr;
  igi2_frame.ptDynCubeObj = sqrt(v5 * v5 + v4 * v4 + v3 * v3) + *(float *)&ptQTask[8].ptNext;
  World_RegisterDynCubeObjFirstTimeRadius(
    v2->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.ptPos,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptQTask[30].tQTaskRefList.ptMiddle = (struct QReference_s *)HumanSoldier_StateSignalHandler;
  ptQTask[30].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_apfState;
  ptQTask[30].ptParent = (struct QTask_s *)HumanSoldier_apfExitState;
  *(_DWORD *)&ptQTask[30].eQTaskType = 0;
  ptQTask[31].ptPrev = nullptr;
  ptQTask[31].ptNext = (struct QTask_s *)-1;
  ptQTask[31].tQTaskChildren.ptHead = (struct QTask_s *)HumanSoldier_apfState[0];
  ptQTask[31].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[31].tQTaskRefList.ptHead = (struct QReference_s *)HumanSoldier_atSequence;
  ptQTask[31].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  memset(&ptQTask[31].tQTaskRefList.ptMiddle, 0, sizeof(struct QTask_s));
  ptQTask[32].tQTaskRefList.ptMiddle = (struct QReference_s *)HumanSoldier_atStateData;
  ptQTask[44].ptPrev = nullptr;
  ptQTask[44].tQTaskChildren.ptHead = (struct QTask_s *)1166016512;
  BYTE2(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
  *(_DWORD *)&ptQTask[74].eQTaskType = 1;
  ptQTask[75].ptNext = (struct QTask_s *)-1;
  BYTE1(ptQTask[75].ptPrev) = 0;
  ptNext = ptQTask[33].ptNext;
  LOBYTE(ptQTask[75].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[75].ptPrev) = 1;
  ptQTask[75].ptParent = nullptr;
  *(_DWORD *)&ptQTask[75].eQTaskType = 0;
  BYTE1(ptQTask[75].tQTaskRefList.ptTail) = 0;
  if ( ptNext )
    ptNext[1].tQTaskRefList.ptHead = (struct QReference_s *)1;
  ptQTask[75].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[75].tQTaskChildren.ptTail = nullptr;
  ptQTask[74].ptParent = nullptr;
  ptQTask[76].tQTaskChildren.ptHead = nullptr;
  ptQTask[76].tQTaskChildren.ptTail = nullptr;
  ptQTask[76].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[76].ptPrev = nullptr;
  ptQTask[75].tQTaskChildren.ptHead = (struct QTask_s *)1051260355;
  ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanSoldier_IdleUpperBodySignalHandler;
}

// source: j/0/human/soldiertypes/humansoldier.c:5605  [anchor-mhash]
struct HumanSoldier_t *__cdecl HumanSoldier_UpdateVisibilityFactor(
        struct HumanSoldier_t *ptHumanSoldier)
{
  double v1; // st7
  int v2; // ecx

  v1 = *(float *)&ptHumanSoldier->tHuman.pxPrivateData;
  v2 = ptHumanSoldier->tHuman.ePose - 1;
  ptHumanSoldier->tHuman.vGroundTolerance = *(float *)&ptHumanSoldier->tHuman.pxPrivateData;
  if ( v2 )
  {
    if ( v2 == 1 )
      ptHumanSoldier->tHuman.vGroundTolerance = v1 * 0.6000000238418579;
  }
  else
  {
    ptHumanSoldier->tHuman.vGroundTolerance = v1 * 0.800000011920929;
  }
  return ptHumanSoldier;
}

// source: j/0/human/soldiertypes/humansoldier.c:5628  [anchor-mhash]
void __cdecl HumanSoldier_UpdateSector(struct HumanSoldier_t *ptHumanSoldier)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct GraphNode_s *ptN1; };
    struct { struct GraphNode_s *ptN1a; };
    struct { char igi2_o2[4]; struct real64x3_t tP1; };
    struct { char igi2_o3[28]; double v12; };
    struct { char igi2_o4[36]; struct real32x3_t tD1; };
    struct { char igi2_o5[52]; struct real64x3_t tP2; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHitSoundQTaskRef; // edi
  struct Graph_s *ptPrev; // esi
  struct GraphNode_s *Node; // esi
  struct GraphNode_s *v4; // eax
  enum bool ptSectorQTask; // edi
  double v6; // st7
  double vY; // st6
  double vX; // st5

  ptHitSoundQTaskRef = ptHumanSoldier->tHuman.ptHitSoundQTaskRef;
  ptPrev = (struct Graph_s *)ptHitSoundQTaskRef[2427].ptPrev;
  if ( ptPrev )
  {
    if ( ptHitSoundQTaskRef[41].ptPrev )
    {
      igi2_frame.ptN1a = Graph_GetNode(ptPrev, (int)ptHitSoundQTaskRef[40].pxObject);
      Node = Graph_GetNode((struct Graph_s *)ptHitSoundQTaskRef[2427].ptPrev, (int)ptHitSoundQTaskRef[41].ptNext);
      v4 = igi2_frame.ptN1a;
      ptSectorQTask = (enum bool)igi2_frame.ptN1a->ptSectorQTask;
      igi2_frame.ptN1 = (struct GraphNode_s *)Node->ptSectorQTask;
      if ( (struct GraphNode_s *)ptSectorQTask != igi2_frame.ptN1 )
      {
        Graph_GetNodePos(&igi2_frame.tP1, v4);
        Graph_GetNodePos(&igi2_frame.tP2, Node);
        igi2_frame.tD1.vX = igi2_frame.tP1.vX - ptHumanSoldier->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        igi2_frame.tD1.vY = igi2_frame.tP1.vY - ptHumanSoldier->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        v6 = igi2_frame.tP1.vZ - ptHumanSoldier->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
        *(float *)&igi2_frame.tP1.vX = igi2_frame.tP2.vX - ptHumanSoldier->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        *((float *)&igi2_frame.tP1.vX + 1) = igi2_frame.tP2.vY - ptHumanSoldier->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        *(float *)&igi2_frame.tP1.vY = igi2_frame.tP2.vZ - ptHumanSoldier->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
        vY = igi2_frame.tD1.vY;
        vX = igi2_frame.tD1.vX;
        *(double *)&igi2_frame.tD1.vX = *(float *)&igi2_frame.tP1.vY;
        igi2_frame.v12 = *((float *)&igi2_frame.tP1.vX + 1);
        igi2_frame.tP1.vX = *(float *)&igi2_frame.tP1.vX;
        if ( sqrt(igi2_frame.tP1.vX * igi2_frame.tP1.vX + igi2_frame.v12 * igi2_frame.v12 + *(float *)&igi2_frame.tP1.vY * *(float *)&igi2_frame.tP1.vY) <= sqrt(vX * vX + vY * vY + v6 * v6) )
          ptSectorQTask = (enum bool)igi2_frame.ptN1;
      }
      ptHumanSoldier->tStateContext.tDieContext.isSoundPlayed = ptSectorQTask;
    }
    else
    {
      ptHumanSoldier->tStateContext.tDieContext.isSoundPlayed = (enum bool)Graph_GetNode(
                                                                                 ptPrev,
                                                                                 (int)ptHitSoundQTaskRef[2495].pxObject)->ptSectorQTask;
    }
  }
  else
  {
    ptHumanSoldier->tStateContext.tDieContext.isSoundPlayed = false;
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5687  [size]
void __cdecl HumanSoldier_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // eax

  v1 = QTask_NewQTaskRef(ptQTask);
  QVector_AddElement(RunDelayed_ptRunDelayedQTaskRefVector, v1);
}

// source: j/0/human/soldiertypes/humansoldier.c:5701  [anchor-mhash]
void __cdecl HumanSoldier_RunDelayedHandler(struct QTask_s *ptQTask)
{
  double v1; // st7
  int v2; // eax

  if ( ptQTask[34].tQTaskChildren.ptTail )
    ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)(double)AnimController_nTicksPerFrame;
  v1 = *(float *)&ptQTask[49].ptParent;
  v2 = *(_DWORD *)&ptQTask[32].eQTaskType - 1;
  ptQTask[49].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[49].ptParent;
  ptQTask[75].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  if ( v2 )
  {
    if ( v2 == 1 )
      *(float *)&ptQTask[49].tQTaskRefList.ptMiddle = v1 * 0.6000000238418579;
  }
  else
  {
    *(float *)&ptQTask[49].tQTaskRefList.ptMiddle = v1 * 0.800000011920929;
  }
  HumanSoldier_UpdateSector((struct HumanSoldier_t *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][Human_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:5738  [size]
void __cdecl HumanSoldier_ShouldersCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  double v3; // st7
  double v4; // st6
  double v5; // st7
  long double v6; // st6
  long double v7; // rt0
  long double v8; // rt1
  long double v9; // st5
  long double v10; // st3
  double v11; // st6
  double v12; // st5
  long double v13; // st7
  long double v14; // st6
  long double v15; // st6
  long double v16; // st5
  double v17; // st4
  long double v18; // st3
  double v19; // st7
  double v20; // st6
  int nOps; // ecx
  double vY; // st5
  long double v23; // st3
  float v24; // [esp+4h] [ebp-44h]
  float v_I; // [esp+8h] [ebp-40h]
  float v_Ia; // [esp+8h] [ebp-40h]
  float v_H; // [esp+Ch] [ebp-3Ch]
  float v_Ha; // [esp+Ch] [ebp-3Ch]
  float v_Hb; // [esp+Ch] [ebp-3Ch]
  float v_G; // [esp+10h] [ebp-38h]
  float v_Ga; // [esp+10h] [ebp-38h]
  float v_Gb; // [esp+10h] [ebp-38h]
  float v_F; // [esp+14h] [ebp-34h]
  float v_Fa; // [esp+14h] [ebp-34h]
  float v_Fb; // [esp+14h] [ebp-34h]
  float v_D; // [esp+18h] [ebp-30h]
  float v_Da; // [esp+18h] [ebp-30h]
  float v_Db; // [esp+18h] [ebp-30h]
  float v_A; // [esp+1Ch] [ebp-2Ch]
  float v_Aa; // [esp+1Ch] [ebp-2Ch]
  float v_Ab; // [esp+1Ch] [ebp-2Ch]
  float tQuat; // [esp+20h] [ebp-28h]
  float tQuat_8; // [esp+28h] [ebp-20h]
  float tQuat_12; // [esp+2Ch] [ebp-1Ch]
  float tQuat_12a; // [esp+2Ch] [ebp-1Ch]
  float tGammaQuat_8; // [esp+3Ch] [ebp-Ch]
  float ptBoneDynCubeObja = *(float *)&ptBoneDynCubeObj; // [esp+4Ch] [ebp+4h] ARGSLOT
  float ptBoneDynCubeObjb = *(float *)&ptBoneDynCubeObj; // [esp+4Ch] [ebp+4h] ARGSLOT
  float ptBoneDynCubeObjc = *(float *)&ptBoneDynCubeObj; // [esp+4Ch] [ebp+4h] ARGSLOT

  if ( !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    v3 = *(float *)ptBoneDynCubeObj[7].tModelObj.aptAnimTexIndex;
    if ( v3 >= 0.0 )
      v4 = 0.24705882370471954;
    else
      v4 = 0.17777778208255768;
    v5 = v3 * v4;
    v6 = ptBoneDynCubeObj[7].tModelObj.tScale.vZ * 0.5;
    tGammaQuat_8 = sin(v6);
    v7 = cos(v6);
    v8 = sin(v5 * 0.5);
    v9 = cos(v5 * 0.5);
    v_A = 0.0 * tGammaQuat_8;
    v_D = (v9 - v8) * tGammaQuat_8;
    v_F = v8 * tGammaQuat_8;
    v24 = v7;
    v_G = v9 * v24;
    v10 = v9 * v24;
    v_H = v10;
    v_I = v10 + v_G + v_F;
    ptBoneDynCubeObja = (v8 * tGammaQuat_8 + v_I) * 0.5;
    tQuat = (v8 + v9) * v24 + ptBoneDynCubeObja - v_I;
    v11 = v24 * 0.0 + ptBoneDynCubeObja - v_H;
    tQuat_8 = ptBoneDynCubeObja + v_D - v_G;
    tQuat_12 = ptBoneDynCubeObja + v_A - v_F;
    v12 = -tGammaQuat_8;
    v_Ha = (tQuat_8 - v11) * -v12;
    v_Aa = (tQuat_12 - tQuat) * v12;
    v_Da = (tQuat_8 + v11) * v24;
    v_Ga = (tQuat + tQuat_8) * 0.0;
    v_Fa = (tQuat_12 + v11) * (v7 - v12);
    v13 = (tQuat_12 - v11) * (v7 - tGammaQuat_8);
    v14 = v_Fa + v13 + v_Ga;
    ptBoneDynCubeObjb = ((tQuat_8 - tQuat) * 0.0 + v14) * 0.5;
    v15 = (tQuat + tQuat_12) * v24 + ptBoneDynCubeObjb - v14;
    v16 = ptBoneDynCubeObjb + v_Aa - v13;
    v17 = ptBoneDynCubeObjb + v_Da - v_Fa;
    tQuat_12a = ptBoneDynCubeObjb + v_Ha - v_Ga;
    v_Db = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * (v17 - v16);
    v_Ab = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * (v17 + v16);
    v_Ia = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * (v15 + v17);
    v_Hb = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * (tQuat_12a + v16);
    v18 = (ptBone->tOrientation.vW + ptBone->tOrientation.vZ) * (tQuat_12a - v16);
    v_Gb = v18;
    v_Fb = v18 + v_Hb + v_Ia;
    ptBoneDynCubeObjc = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * (v17 - v15) + v_Fb) * 0.5;
    ptBone->tOrientation.vX = (tQuat_12a + v15) * (ptBone->tOrientation.vX + ptBone->tOrientation.vW)
                            + ptBoneDynCubeObjc
                            - v_Fb;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (tQuat_12a - v15)
                            + ptBoneDynCubeObjc
                            - v_Gb;
    v19 = ptBoneDynCubeObjc + v_Ab - v_Hb;
    ptBone->tOrientation.vZ = v19;
    v20 = ptBoneDynCubeObjc + v_Db - v_Ia;
    nOps = ptBone->tOrientation.nOps;
    ptBone->tOrientation.vW = v20;
    nOps += 3;
    ptBone->tOrientation.nOps = nOps;
    if ( nOps > 1000 )
    {
      vY = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v23 = 1.0 / sqrt(v20 * v20 + v19 * v19 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + vY * vY);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v23;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v23;
      ptBone->tOrientation.vZ = v19 * v23;
      ptBone->tOrientation.vW = v20 * v23;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5785  [size]
void __cdecl HumanSoldier_UpperBackCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  double v3; // st7
  double v4; // st6
  double v5; // st7
  long double v6; // st6
  long double v7; // rt0
  long double v8; // rt1
  long double v9; // st5
  long double v10; // st3
  double v11; // st6
  double v12; // st5
  long double v13; // st7
  long double v14; // st6
  long double v15; // st6
  long double v16; // st5
  double v17; // st4
  long double v18; // st3
  double v19; // st7
  double v20; // st6
  int nOps; // ecx
  double vY; // st5
  long double v23; // st3
  float v24; // [esp+4h] [ebp-44h]
  float v_I; // [esp+8h] [ebp-40h]
  float v_Ia; // [esp+8h] [ebp-40h]
  float v_H; // [esp+Ch] [ebp-3Ch]
  float v_Ha; // [esp+Ch] [ebp-3Ch]
  float v_Hb; // [esp+Ch] [ebp-3Ch]
  float v_G; // [esp+10h] [ebp-38h]
  float v_Ga; // [esp+10h] [ebp-38h]
  float v_Gb; // [esp+10h] [ebp-38h]
  float v_F; // [esp+14h] [ebp-34h]
  float v_Fa; // [esp+14h] [ebp-34h]
  float v_Fb; // [esp+14h] [ebp-34h]
  float v_D; // [esp+18h] [ebp-30h]
  float v_Da; // [esp+18h] [ebp-30h]
  float v_Db; // [esp+18h] [ebp-30h]
  float v_A; // [esp+1Ch] [ebp-2Ch]
  float v_Aa; // [esp+1Ch] [ebp-2Ch]
  float v_Ab; // [esp+1Ch] [ebp-2Ch]
  float tQuat; // [esp+20h] [ebp-28h]
  float tQuat_8; // [esp+28h] [ebp-20h]
  float tQuat_12; // [esp+2Ch] [ebp-1Ch]
  float tQuat_12a; // [esp+2Ch] [ebp-1Ch]
  float tGammaQuat_8; // [esp+3Ch] [ebp-Ch]
  float ptBoneDynCubeObja = *(float *)&ptBoneDynCubeObj; // [esp+4Ch] [ebp+4h] ARGSLOT
  float ptBoneDynCubeObjb = *(float *)&ptBoneDynCubeObj; // [esp+4Ch] [ebp+4h] ARGSLOT
  float ptBoneDynCubeObjc = *(float *)&ptBoneDynCubeObj; // [esp+4Ch] [ebp+4h] ARGSLOT

  if ( !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    v3 = *(float *)ptBoneDynCubeObj[7].tModelObj.aptAnimTexIndex;
    if ( v3 >= 0.0 )
      v4 = 0.33529412746429443;
    else
      v4 = 0.31111112236976624;
    v5 = v3 * v4;
    v6 = ptBoneDynCubeObj[7].tModelObj.tScale.vZ * 0.5;
    tGammaQuat_8 = sin(v6);
    v7 = cos(v6);
    v8 = sin(v5 * 0.5);
    v9 = cos(v5 * 0.5);
    v_A = 0.0 * tGammaQuat_8;
    v_D = (v9 - v8) * tGammaQuat_8;
    v_F = v8 * tGammaQuat_8;
    v24 = v7;
    v_G = v9 * v24;
    v10 = v9 * v24;
    v_H = v10;
    v_I = v10 + v_G + v_F;
    ptBoneDynCubeObja = (v8 * tGammaQuat_8 + v_I) * 0.5;
    tQuat = (v8 + v9) * v24 + ptBoneDynCubeObja - v_I;
    v11 = v24 * 0.0 + ptBoneDynCubeObja - v_H;
    tQuat_8 = ptBoneDynCubeObja + v_D - v_G;
    tQuat_12 = ptBoneDynCubeObja + v_A - v_F;
    v12 = -tGammaQuat_8;
    v_Ha = (tQuat_8 - v11) * -v12;
    v_Aa = (tQuat_12 - tQuat) * v12;
    v_Da = (tQuat_8 + v11) * v24;
    v_Ga = (tQuat + tQuat_8) * 0.0;
    v_Fa = (tQuat_12 + v11) * (v7 - v12);
    v13 = (tQuat_12 - v11) * (v7 - tGammaQuat_8);
    v14 = v_Fa + v13 + v_Ga;
    ptBoneDynCubeObjb = ((tQuat_8 - tQuat) * 0.0 + v14) * 0.5;
    v15 = (tQuat + tQuat_12) * v24 + ptBoneDynCubeObjb - v14;
    v16 = ptBoneDynCubeObjb + v_Aa - v13;
    v17 = ptBoneDynCubeObjb + v_Da - v_Fa;
    tQuat_12a = ptBoneDynCubeObjb + v_Ha - v_Ga;
    v_Db = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * (v17 - v16);
    v_Ab = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * (v17 + v16);
    v_Ia = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * (v15 + v17);
    v_Hb = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * (tQuat_12a + v16);
    v18 = (ptBone->tOrientation.vW + ptBone->tOrientation.vZ) * (tQuat_12a - v16);
    v_Gb = v18;
    v_Fb = v18 + v_Hb + v_Ia;
    ptBoneDynCubeObjc = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * (v17 - v15) + v_Fb) * 0.5;
    ptBone->tOrientation.vX = (tQuat_12a + v15) * (ptBone->tOrientation.vX + ptBone->tOrientation.vW)
                            + ptBoneDynCubeObjc
                            - v_Fb;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (tQuat_12a - v15)
                            + ptBoneDynCubeObjc
                            - v_Gb;
    v19 = ptBoneDynCubeObjc + v_Ab - v_Hb;
    ptBone->tOrientation.vZ = v19;
    v20 = ptBoneDynCubeObjc + v_Db - v_Ia;
    nOps = ptBone->tOrientation.nOps;
    ptBone->tOrientation.vW = v20;
    nOps += 3;
    ptBone->tOrientation.nOps = nOps;
    if ( nOps > 1000 )
    {
      vY = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v23 = 1.0 / sqrt(v20 * v20 + v19 * v19 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + vY * vY);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v23;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v23;
      ptBone->tOrientation.vZ = v19 * v23;
      ptBone->tOrientation.vW = v20 * v23;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5832  [anchor-mhash]
void __cdecl HumanSoldier_LowerBackCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v48; };
    struct { char igi2_o1[36]; float v_J; };
    struct { char igi2_o2[40]; float v_I; };
    struct { char igi2_o3[44]; float v_H; };
    struct { char igi2_o4[48]; float v_G; };
    struct { char igi2_o5[52]; float v_F; };
    struct { char igi2_o6[56]; float vAlpha; };
    struct { char igi2_o7[60]; float v_D; };
    struct { char igi2_o8[64]; float v_A; };
    struct { char igi2_o9[68]; float v57; };
    struct { char igi2_o10[72]; struct real64x3_t tDirection; };
    struct { char igi2_o11[96]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st6
  double v5; // st7
  float v6; // eax
  float vY; // eax
  double v8; // st7
  double v9; // st6
  int v10; // eax
  int nOps; // edx
  double v12; // st5
  double v13; // st4
  int v14; // edx
  double v15; // st7
  double v16; // st6
  double v17; // st5
  long double v18; // rt1
  double v19; // st6
  double v20; // st7
  int v21; // eax
  double vX; // st6
  long double v23; // st6
  long double v24; // st7
  int v25; // edx
  long double v26; // st7
  long double v27; // st6
  long double v28; // st7
  long double v29; // st6
  long double v30; // st5
  double v31; // st7
  double v32; // st6
  double v33; // st5
  long double v34; // st3
  double v35; // st7
  double v36; // st6
  long double v37; // st7
  long double v38; // rt1
  long double v39; // st6
  long double v40; // st5
  long double v41; // st4
  int v42; // eax
  bool v43; // sf
  double v44; // st7
  double v45; // st6
  double v46; // st5
  long double v47; // st3

  if ( LODWORD(ptBoneDynCubeObj[4].avMorphWeights[7])
    && !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14])
    && (LOBYTE(ptBoneDynCubeObj[7].tModelObj.tRelativeOrientation.tZ.vY) & 1) == 0 )
  {
    HumanAI_GetTargetPosition(&igi2_frame.tDirection, (struct HumanAI_s *)LODWORD(ptBoneDynCubeObj[4].avMorphWeights[7]));
    if ( Real64x3_NullVector(&igi2_frame.tDirection) )
      goto LABEL_6;
    v3 = igi2_frame.tDirection.vX - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX;
    v4 = igi2_frame.tDirection.vY - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY;
    igi2_frame.tDirection.vZ = igi2_frame.tDirection.vZ - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ;
    igi2_frame.tDirection.vX = v3 - ptParent->tTranslation.vX;
    igi2_frame.tDirection.vY = v4 - ptParent->tTranslation.vY;
    igi2_frame.tDirection.vZ = igi2_frame.tDirection.vZ - ptParent->tTranslation.vZ;
    igi2_frame.Real64x3_RotateInverse_tTemp.vX = ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vX * igi2_frame.tDirection.vZ
                                    + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vX * igi2_frame.tDirection.vY
                                    + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vX * igi2_frame.tDirection.vX;
    igi2_frame.Real64x3_RotateInverse_tTemp.vY = ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vY * igi2_frame.tDirection.vZ
                                    + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vY * igi2_frame.tDirection.vY
                                    + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vY * igi2_frame.tDirection.vX;
    igi2_frame.Real64x3_RotateInverse_tTemp.vZ = ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vZ * igi2_frame.tDirection.vZ
                                    + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vZ * igi2_frame.tDirection.vY
                                    + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vZ * igi2_frame.tDirection.vX;
    qmemcpy(&igi2_frame.tDirection, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.tDirection));
    if ( igi2_frame.Real64x3_RotateInverse_tTemp.vY < 4096.0 )
    {
LABEL_6:
      igi2_frame.tDirection.vX = 0.0;
      igi2_frame.tDirection.vY = 4096.0;
      igi2_frame.tDirection.vZ = 0.0;
    }
    qmemcpy(&igi2_frame.v48, &igi2_frame.tDirection, sizeof(igi2_frame.v48));
    igi2_frame.vAlpha = GameFunctions_CalcAlpha(igi2_frame.v48);
    qmemcpy(&igi2_frame.v48, &igi2_frame.tDirection, sizeof(igi2_frame.v48));
    v5 = GameFunctions_CalcGamma(igi2_frame.v48);
    if ( v5 >= -1.0471975803375244 )
    {
      if ( v5 > 1.0471975803375244 )
        v5 = 1.0471975803375244;
    }
    else
    {
      v5 = -1.0471975803375244;
    }
    v6 = igi2_frame.vAlpha;
    ptBoneDynCubeObj[7].tModelObj.tScale.vZ = v5;
    *(float *)ptBoneDynCubeObj[7].tModelObj.aptAnimTexIndex = v6;
    vY = ptBoneDynCubeObj[3].tModelObj.tRelativeOrientation.tY.vY;
    if ( vY != 0.0 )
    {
      v8 = -ptParent->tOrientation.vX;
      HIDWORD(igi2_frame.tDirection.vY) = LODWORD(ptParent->tOrientation.vW);
      v9 = -ptParent->tOrientation.vY;
      v10 = **(_DWORD **)(LODWORD(vY) + 80);
      nOps = ptParent->tOrientation.nOps;
      v12 = -ptParent->tOrientation.vZ;
      igi2_frame.v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * (v12 - v9);
      igi2_frame.vAlpha = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (*((float *)&igi2_frame.tDirection.vY + 1) - v8);
      igi2_frame.v_D = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * (v12 + v9);
      igi2_frame.v_F = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * (v12 + v8);
      igi2_frame.v_G = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * (*((float *)&igi2_frame.tDirection.vY + 1) + v9);
      v13 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * (*((float *)&igi2_frame.tDirection.vY + 1) - v9);
      igi2_frame.v_H = v13;
      igi2_frame.v_I = v13 + igi2_frame.v_G + igi2_frame.v_F;
      igi2_frame.v_J = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * (v12 - v8) + igi2_frame.v_I) * 0.5;
      v14 = nOps + ptBone->tOrientation.nOps + 1;
      v15 = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * (*((float *)&igi2_frame.tDirection.vY + 1) + v8) + igi2_frame.v_J - igi2_frame.v_I;
      v16 = igi2_frame.v_J + igi2_frame.vAlpha - igi2_frame.v_H;
      v17 = igi2_frame.v_J + igi2_frame.v_D - igi2_frame.v_G;
      *((float *)&igi2_frame.tDirection.vY + 1) = igi2_frame.v_J + igi2_frame.v_A - igi2_frame.v_F;
      if ( v14 > 1000 )
      {
        v14 = 0;
        v18 = 1.0
            / sqrt(*((float *)&igi2_frame.tDirection.vY + 1) * *((float *)&igi2_frame.tDirection.vY + 1) + v17 * v17 + v16 * v16 + v15 * v15);
        v15 = v15 * v18;
        v16 = v16 * v18;
        v17 = v17 * v18;
        *((float *)&igi2_frame.tDirection.vY + 1) = *((float *)&igi2_frame.tDirection.vY + 1) * v18;
      }
      igi2_frame.v57 = (*(float *)(v10 + 20) - *(float *)(v10 + 16)) * (v16 - v17);
      igi2_frame.v_A = (*(float *)(v10 + 24) - *(float *)(v10 + 12)) * (v17 + v16);
      igi2_frame.v_D = (*(float *)(v10 + 16) + *(float *)(v10 + 20)) * (*((float *)&igi2_frame.tDirection.vY + 1) - v15);
      igi2_frame.vAlpha = (v16 + v15) * (*(float *)(v10 + 20) + *(float *)(v10 + 12));
      igi2_frame.v_H = (*(float *)(v10 + 24) + *(float *)(v10 + 16)) * (*((float *)&igi2_frame.tDirection.vY + 1) - v17);
      igi2_frame.v_G = (*(float *)(v10 + 24) - *(float *)(v10 + 16)) * (*((float *)&igi2_frame.tDirection.vY + 1) + v17);
      igi2_frame.v_F = igi2_frame.v_G + igi2_frame.v_H + igi2_frame.vAlpha;
      v19 = ((v15 - v16) * (*(float *)(v10 + 20) - *(float *)(v10 + 12)) + igi2_frame.v_F) * 0.5;
      ptBone->tOrientation.vX = (*(float *)(v10 + 24) + *(float *)(v10 + 12)) * (*((float *)&igi2_frame.tDirection.vY + 1) + v15)
                              + v19
                              - igi2_frame.v_F;
      igi2_frame.v_J = igi2_frame.v_A + v19 - igi2_frame.v_G;
      ptBone->tOrientation.vY = igi2_frame.v_J;
      igi2_frame.v_I = igi2_frame.v_D + v19 - igi2_frame.v_H;
      ptBone->tOrientation.vZ = igi2_frame.v_I;
      v20 = v19 + igi2_frame.v57 - igi2_frame.vAlpha;
      ptBone->tOrientation.vW = v20;
      v21 = *(_DWORD *)(v10 + 28) + v14 + 1;
      ptBone->tOrientation.nOps = v21;
      if ( v21 > 1000 )
      {
        vX = ptBone->tOrientation.vX;
        ptBone->tOrientation.nOps = 0;
        v23 = 1.0 / sqrt(v20 * v20 + igi2_frame.v_I * igi2_frame.v_I + igi2_frame.v_J * igi2_frame.v_J + vX * vX);
        ptBone->tOrientation.vX = ptBone->tOrientation.vX * v23;
        ptBone->tOrientation.vY = igi2_frame.v_J * v23;
        ptBone->tOrientation.vZ = igi2_frame.v_I * v23;
        ptBone->tOrientation.vW = v20 * v23;
      }
    }
    v24 = ptBoneDynCubeObj[7].tModelObj.tScale.vZ * 0.5;
    v25 = ptBone->tOrientation.nOps + 1;
    ptBone->tOrientation.nOps = v25;
    igi2_frame.vAlpha = v24;
    v26 = sin(v24);
    v27 = cos(igi2_frame.vAlpha);
    igi2_frame.vAlpha = v26;
    igi2_frame.v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * igi2_frame.vAlpha;
    igi2_frame.v57 = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * v26;
    igi2_frame.v_H = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * v26;
    v28 = v27;
    igi2_frame.v_F = v27;
    igi2_frame.v_G = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * igi2_frame.v_F;
    v29 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * v27;
    v30 = igi2_frame.v_G + v29 + igi2_frame.v_H;
    igi2_frame.v_J = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * igi2_frame.vAlpha + v30) * 0.5;
    ptBone->tOrientation.vX = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * igi2_frame.v_F + igi2_frame.v_J - v30;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * v28 + igi2_frame.v_J - v29;
    v31 = igi2_frame.v_J + igi2_frame.v57 - igi2_frame.v_G;
    ptBone->tOrientation.vZ = v31;
    v32 = igi2_frame.v_J + igi2_frame.v_A - igi2_frame.v_H;
    ptBone->tOrientation.vW = v32;
    if ( v25 > 1000 )
    {
      v33 = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v34 = 1.0 / sqrt(v32 * v32 + v31 * v31 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + v33 * v33);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v34;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v34;
      ptBone->tOrientation.vZ = v31 * v34;
      ptBone->tOrientation.vW = v32 * v34;
    }
    v35 = *(float *)ptBoneDynCubeObj[7].tModelObj.aptAnimTexIndex;
    if ( v35 >= 0.0 )
      v36 = 0.3235294222831726;
    else
      v36 = 0.5;
    v37 = v35 * v36 * 0.5;
    v38 = sin(v37);
    v39 = cos(v37);
    igi2_frame.v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * 0.0;
    igi2_frame.v57 = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * 0.0;
    igi2_frame.v_F = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * v38;
    igi2_frame.vAlpha = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * v39;
    v40 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * v39;
    v41 = igi2_frame.vAlpha + v40 + igi2_frame.v_F;
    igi2_frame.v_J = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * -v38 + v41) * 0.5;
    ptBone->tOrientation.vX = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * (v39 + v38) + igi2_frame.v_J - v41;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (v39 - v38) + igi2_frame.v_J - v40;
    v42 = ptBone->tOrientation.nOps + 1;
    v43 = ptBone->tOrientation.nOps - 999 < 0;
    v44 = igi2_frame.v_J + igi2_frame.v57 - igi2_frame.vAlpha;
    ptBone->tOrientation.nOps = v42;
    ptBone->tOrientation.vZ = v44;
    v45 = igi2_frame.v_J + igi2_frame.v_A - igi2_frame.v_F;
    ptBone->tOrientation.vW = v45;
    if ( !(v43 ^ __OFSUB__(v42, 1000) | (v42 == 1000)) )
    {
      v46 = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v47 = 1.0 / sqrt(v45 * v45 + v44 * v44 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + v46 * v46);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v47;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v47;
      ptBone->tOrientation.vZ = v44 * v47;
      ptBone->tOrientation.vW = v45 * v47;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5940  [anchor-mhash]
void __cdecl HumanSoldier_HeadCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  float v3; // eax
  long double v4; // st7
  long double v5; // rt0
  long double v6; // st7
  long double v7; // st6
  long double v8; // st7
  int v9; // edx
  double v10; // st6
  double vX; // st5
  long double v12; // st5
  float v_Ga; // [esp+0h] [ebp-28h]
  float v_G; // [esp+0h] [ebp-28h]
  float v_F; // [esp+4h] [ebp-24h]
  float v_C; // [esp+8h] [ebp-20h]
  float v_D; // [esp+Ch] [ebp-1Ch]
  float v_A; // [esp+10h] [ebp-18h]
  float tQuat_12; // [esp+20h] [ebp-8h]
  float ptBoneDynCubeObja = *(float *)&ptBoneDynCubeObj; // [esp+2Ch] [ebp+4h] ARGSLOT

  v3 = ptBoneDynCubeObj[4].avMorphWeights[7];
  if ( v3 != 0.0 && !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    v4 = *(float *)(LODWORD(v3) + 256) * 0.5;
    v5 = sin(v4);
    tQuat_12 = cos(v4);
    v_A = (ptBone->tOrientation.vZ - ptBone->tOrientation.vY) * -v5;
    v_C = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * v5;
    v_D = (ptBone->tOrientation.vY + ptBone->tOrientation.vZ) * tQuat_12;
    v_F = (ptBone->tOrientation.vZ + ptBone->tOrientation.vX) * 0.0;
    v_Ga = (ptBone->tOrientation.vY + ptBone->tOrientation.vW) * (tQuat_12 - v5);
    v6 = (tQuat_12 + v5) * (ptBone->tOrientation.vW - ptBone->tOrientation.vY);
    v7 = v_Ga + v6 + v_F;
    ptBoneDynCubeObja = ((ptBone->tOrientation.vZ - ptBone->tOrientation.vX) * 0.0 + v7) * 0.5;
    ptBone->tOrientation.vX = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * tQuat_12 + ptBoneDynCubeObja - v7;
    v8 = ptBoneDynCubeObja + v_C - v6;
    ptBone->tOrientation.vY = v8;
    v9 = ptBone->tOrientation.nOps + 1;
    ptBone->tOrientation.nOps = v9;
    v_G = ptBoneDynCubeObja + v_D - v_Ga;
    ptBone->tOrientation.vZ = v_G;
    v10 = ptBoneDynCubeObja + v_A - v_F;
    ptBone->tOrientation.vW = v10;
    if ( v9 > 1000 )
    {
      vX = ptBone->tOrientation.vX;
      ptBone->tOrientation.nOps = 0;
      v12 = 1.0 / sqrt(v10 * v10 + v_G * v_G + v8 * v8 + vX * vX);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v12;
      ptBone->tOrientation.vY = v8 * v12;
      ptBone->tOrientation.vZ = v_G * v12;
      ptBone->tOrientation.vW = v10 * v12;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:5974  [anchor-mhash]
void __cdecl HumanSoldier_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][Human_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:6000  [size]
void __cdecl HumanSoldier_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanSoldier_ptParameterList;
}

// source: j/0/human/soldiertypes/humansoldier.c:6016  [anchor-mhash]
void __cdecl HumanSoldier_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][Human_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    *(_DWORD *)(80 * (int)ptQTask[36].ptNext + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanSoldier_ShouldersCallback;
    *(_DWORD *)(80 * (int)ptQTask[35].ptParent + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanSoldier_LowerBackCallback;
    *(_DWORD *)(80 * *(_DWORD *)&ptQTask[35].eQTaskType + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanSoldier_UpperBackCallback;
    *(_DWORD *)(80 * (int)ptQTask[35].tQTaskRefList.ptMiddle + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanSoldier_HeadCallback;
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:6052  [anchor-mhash]
void __cdecl HumanSoldier_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // esi
  struct QTask_s *ptParent; // eax
  int v3; // eax
  int v4; // edx
  struct QTask_s **p_ptParent; // ecx
  struct QReference_s *v6; // eax
  struct QTaskList_s *v7; // ebx

  v1 = ptQTask;
  ptParent = ptQTask[48].ptParent;
  if ( ptParent )
  {
    v3 = 1020 * (int)ptParent[110].tQTaskChildren.ptTail + 139173824;
    ptQTask[25].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
    v1[25].tQTaskRefList.ptTail = (struct QReference_s *)v3;
    v1[25].tQTaskRefList.ptHead = nullptr;
    v4 = 0;
    p_ptParent = &v1[25].ptParent;
    do
    {
      v6 = &v1[25].tQTaskRefList.ptTail[v4];
      *p_ptParent = nullptr;
      p_ptParent[1] = (struct QTask_s *)v6->ptNext;
      v4 += 5;
      p_ptParent += 2;
    }
    while ( v4 < 85 );
    v1[29].tQTaskChildren.ptHead = (struct QTask_s *)-1;
    v1[29].tQTaskChildren.ptMiddle = nullptr;
    v1[29].tQTaskChildren.ptTail = nullptr;
  }
  if ( v1[10].tQTaskRefList.ptTail == (struct QReference_s *)1
    && !LOBYTE(v1[29].tQTaskRefList.ptHead)
    && Game_iMissionID != 21
    && Game_iMissionID != 22 )
  {
    v7 = AIDetection_ptDetectionQTaskList;
    if ( QTaskList_IsQTaskRegistered(AIDetection_ptDetectionQTaskList, (int *)&ptQTask, v1) )
      QTaskList_Remove(v7, v1);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:6104  [size]
void __cdecl HumanSoldier_HumanUpdateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !LOBYTE(ptQTask[25].tQTaskChildren.ptTail) )
  {
    qmemcpy(&ptQTask[12].ptParent, &ptQTask[19].ptPrev, 0xFCu);
    qmemcpy(&ptQTask[19].ptPrev, *(void **)pxContext, 0xFCu);
  }
  HumanSoldier_Update(ptQTask);
}

// source: j/0/human/soldiertypes/humansoldier.c:6142  [anchor-strings]
void __cdecl HumanSoldier_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v21; };
    struct { char igi2_o1[31]; char v22; };
    struct { char igi2_o2[32]; struct QTask_s *v23; };
    struct { char igi2_o3[32]; int v24; };
    struct { char igi2_o4[32]; int v25; };
    struct { char igi2_o5[36]; float v26; };
    struct { char igi2_o6[43]; bool v27; };
    struct { char igi2_o7[44]; struct QTask_s *v28; };
    struct { char igi2_o8[48]; int v29; };
    struct { char igi2_o9[52]; struct HumanAIEventContext_t ptEventContext; };
    struct { char igi2_o10[116]; _BYTE v31[45]; };
    struct { char igi2_o11[161]; __int16 v32; };
    struct { char igi2_o12[163]; char v33; };
    struct { char igi2_o13[164]; _BYTE v34[29]; };
    struct { char igi2_o14[193]; __int16 v35; };
    struct { char igi2_o15[195]; char v36; };
    struct { char igi2_o16[196]; _BYTE v37[29]; };
    struct { char igi2_o17[225]; __int16 v38; };
    struct { char igi2_o18[227]; char v39; };
    struct { char igi2_o19[228]; _BYTE v40[29]; };
    struct { char igi2_o20[257]; __int16 v41; };
    struct { char igi2_o21[259]; char v42; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ecx
  int v3; // eax
  struct HumanDamage_t *p_tQTaskRefList; // ebx
  int v5; // edx
  void (__cdecl *pfHandler)(int, int *); // ecx
  int v7; // edx
  enum DamagePart_e DamagePartFromWeaponHit; // eax
  struct QTask_s *v9; // eax
  struct QReference_s *ptTail; // ecx
  struct real64x3_t *v11; // eax
  double *v12; // esi
  double vZ; // st7
  int v14; // eax
  void (__cdecl *v15)(int, struct QTask_s **); // ecx
  double *v16; // eax
  double *v17; // eax
  int v18; // eax
  int v19; // eax
  bool v20; // zf

  ptParent = ptQTask[48].ptParent;
  igi2_frame.v28 = (struct QTask_s *)(2752 * Config_tConfig.iActiveProfile + 7392072);
  v3 = *((_DWORD *)pxContext + 5);
  igi2_frame.v23 = ptParent;
  p_tQTaskRefList = (struct HumanDamage_t *)&ptQTask[25].tQTaskRefList;
  igi2_frame.v22 = 0;
  if ( v3 )
  {
    v5 = *((_DWORD *)pxContext + 7);
    if ( v5 )
    {
      if ( *(_BYTE *)(v5 + 177) && !LOBYTE(ptQTask[32].tQTaskRefList.ptTail) )
      {
        igi2_frame.v29 = (int)ptQTask;
        pfHandler = (void (__cdecl *)(int, int *))QTask_aatQTaskFinalEvent[Human_eHitByYouQTaskEvent][*(unsigned __int16 *)(v3 + 36)].pfHandler;
        if ( pfHandler )
          pfHandler(v3, &igi2_frame.v29);
        ptParent = igi2_frame.v23;
      }
    }
  }
  if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
  {
    if ( !ptParent
      || ((v7 = *((_DWORD *)pxContext + 5),
           igi2_frame.v27 = BYTE1(ptParent[111].tQTaskChildren.ptMiddle) == 0,
           igi2_frame.v22 = BYTE2(ptParent[111].tQTaskChildren.ptMiddle),
           !v7)
       || QTask_IsQTaskTypeDerived(*(_WORD *)(v7 + 36), Human_eQTaskType) == false
       || ptQTask[10].tQTaskRefList.ptTail != *(struct QReference_s **)(v7 + 428))
      && igi2_frame.v27 )
    {
      igi2_frame.v29 = 1;
      DamagePartFromWeaponHit = HumanDamage_GetDamagePartFromWeaponHit(
                                  p_tQTaskRefList,
                                  (struct BoneDynCubeObj_s *)ptQTask,
                                  (struct WeaponHitContext_t *)pxContext);
      ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)DamagePartFromWeaponHit;
      if ( (DamagePartFromWeaponHit == HUMANDAMAGE_PART_GROIN || DamagePartFromWeaponHit == HUMANDAMAGE_PART_HEAD)
        && igi2_frame.v22 )
      {
        igi2_frame.v26 = *((float *)pxContext + 1);
      }
      else
      {
        igi2_frame.v26 = *((float *)pxContext + 1);
        if ( *(_DWORD *)(*((_DWORD *)pxContext + 6) + 668) != 3 )
          igi2_frame.v26 = igi2_frame.v26 * p_tQTaskRefList->atDamagePart[DamagePartFromWeaponHit].vDamageMultiplier;
      }
      p_tQTaskRefList->atDamagePart[DamagePartFromWeaponHit].vDamage = igi2_frame.v26
                                                                     + p_tQTaskRefList->atDamagePart[DamagePartFromWeaponHit].vDamage;
      v9 = igi2_frame.v28;
      p_tQTaskRefList->vDamage = igi2_frame.v26 + p_tQTaskRefList->vDamage;
      if ( BYTE1(v9->tQTaskChildren.ptHead) && *(_DWORD *)(*((_DWORD *)pxContext + 6) + 668) == 3 )
      {
        igi2_frame.v28 = *(struct QTask_s **)pxContext;
        RenderMode_tActiveRenderMode.apfRenderModeMethod[BoneDynCubeObj_eCreateBruiseRenderModeMethode](&igi2_frame.v28);
      }
      HumanDamage_CreateFleshEnterEffect(
        p_tQTaskRefList,
        (struct real32x3_t *)((char *)pxContext + 8),
        (struct real64x3_t *)(*(_DWORD *)pxContext + 8),
        ptQTask);
      igi2_frame.v24 = *(_DWORD *)&ptQTask[30].eQTaskType;
      *(float *)&ptQTask[75].tQTaskChildren.ptMiddle = igi2_frame.v26 + *(float *)&ptQTask[75].tQTaskChildren.ptMiddle;
      if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
      {
        v14 = *((_DWORD *)pxContext + 5);
        if ( v14 )
        {
          igi2_frame.v28 = ptQTask;
          v15 = (void (__cdecl *)(int, struct QTask_s **))QTask_aatQTaskFinalEvent[Human_eKilledByYouQTaskEvent][*(unsigned __int16 *)(v14 + 36)].pfHandler;
          if ( v15 )
            v15(v14, &igi2_frame.v28);
        }
        igi2_frame.ptEventContext.eTeam = (int)ptQTask[10].tQTaskRefList.ptTail;
        v16 = *((double **)pxContext + 5);
        igi2_frame.ptEventContext.eEvent = 34;
        igi2_frame.ptEventContext.bFlags = 419;
        igi2_frame.ptEventContext.ptReferenceQTask = nullptr;
        igi2_frame.ptEventContext.ptHumanOriginatorQTask = ptQTask;
        igi2_frame.ptEventContext.ptPosition = (struct real64x3_t *)&ptQTask[1];
        igi2_frame.ptEventContext.vRadius = 122880.0;
        if ( v16 )
        {
          igi2_frame.ptEventContext.tDirection.vX = v16[5] - *(double *)&ptQTask[1].ptNext;
          igi2_frame.ptEventContext.tDirection.vY = v16[6] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
          igi2_frame.ptEventContext.tDirection.vZ = v16[7] - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
        }
        else
        {
          memset(&igi2_frame.ptEventContext.tDirection, 0, sizeof(igi2_frame.ptEventContext.tDirection));
        }
        HumanAI_SendEvent(&igi2_frame.ptEventContext);
        if ( igi2_frame.v26 >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
        {
          igi2_frame.v29 = 0;
        }
        else
        {
          v17 = *((double **)pxContext + 5);
          igi2_frame.ptEventContext.eEvent = 24;
          igi2_frame.ptEventContext.eTeam = -1;
          igi2_frame.ptEventContext.bFlags = 1314;
          igi2_frame.ptEventContext.ptReferenceQTask = nullptr;
          igi2_frame.ptEventContext.ptHumanOriginatorQTask = ptQTask;
          igi2_frame.ptEventContext.ptPosition = (struct real64x3_t *)&ptQTask[1];
          igi2_frame.ptEventContext.vRadius = 20480.0;
          if ( v17 )
          {
            igi2_frame.ptEventContext.tDirection.vX = v17[5] - *(double *)&ptQTask[1].ptNext;
            igi2_frame.ptEventContext.tDirection.vY = v17[6] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
            igi2_frame.ptEventContext.tDirection.vZ = v17[7] - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
          }
          else
          {
            memset(&igi2_frame.ptEventContext.tDirection, 0, sizeof(igi2_frame.ptEventContext.tDirection));
          }
          HumanAI_SendEvent(&igi2_frame.ptEventContext);
        }
        ptQTask[50].tQTaskRefList = *(struct QReferenceList_s *)((char *)pxContext + 8);
        ptQTask[76].ptPrev = *((struct QTask_s **)pxContext + 1);
        v18 = *(_DWORD *)(*((_DWORD *)pxContext + 6) + 668);
        if ( v18 )
        {
          v19 = v18 - 1;
          if ( v19 )
          {
            if ( v19 == 1 )
              ptQTask[76].ptNext = (struct QTask_s *)1;
            else
              ptQTask[76].ptNext = (struct QTask_s *)4;
          }
          else
          {
            ptQTask[76].ptNext = (struct QTask_s *)3;
          }
        }
        else
        {
          ptQTask[76].ptNext = (struct QTask_s *)2;
        }
        igi2_frame.v25 = igi2_frame.v24 | 0x20000;
        LOBYTE(ptQTask[29].tQTaskRefList.ptHead) = 1;
      }
      else
      {
        strcpy(&igi2_frame.v31[16], "GV_69_03");
        memset(&igi2_frame.v31[25], 0, 20);
        igi2_frame.v32 = 0;
        igi2_frame.v33 = 0;
        strcpy(igi2_frame.v34, "GV_70_03");
        strcpy(igi2_frame.v37, "GV_71_03");
        memset(&igi2_frame.v34[9], 0, 20);
        memset(&igi2_frame.v37[9], 0, 20);
        strcpy(igi2_frame.v40, "GV_72_03");
        memset(&igi2_frame.v40[9], 0, 20);
        igi2_frame.v35 = 0;
        igi2_frame.v36 = 0;
        igi2_frame.v38 = 0;
        igi2_frame.v39 = 0;
        igi2_frame.v41 = 0;
        *(_DWORD *)&igi2_frame.v31[4] = igi2_frame.v34;
        igi2_frame.v42 = 0;
        *(_DWORD *)igi2_frame.v31 = &igi2_frame.v31[16];
        *(_DWORD *)&igi2_frame.v31[8] = igi2_frame.v37;
        *(_DWORD *)&igi2_frame.v31[12] = igi2_frame.v40;
        igi2_frame.v25 = igi2_frame.v24 | 0x10000;
        Human_HitSound(ptQTask, (char **)igi2_frame.v31, 4);
        ptTail = ptQTask[10].tQTaskRefList.ptTail;
        v11 = (struct real64x3_t *)(*(_DWORD *)pxContext + 8);
        igi2_frame.ptEventContext.eEvent = 14;
        igi2_frame.ptEventContext.eTeam = (int)ptTail;
        igi2_frame.ptEventContext.bFlags = 34;
        igi2_frame.ptEventContext.ptReferenceQTask = nullptr;
        igi2_frame.ptEventContext.ptHumanOriginatorQTask = ptQTask;
        igi2_frame.ptEventContext.ptPosition = v11;
        v12 = *((double **)pxContext + 5);
        igi2_frame.ptEventContext.vRadius = 20480.0;
        if ( v12 )
        {
          igi2_frame.ptEventContext.tDirection.vX = v12[5] - *(double *)&ptQTask[1].ptNext;
          igi2_frame.ptEventContext.tDirection.vY = v12[6] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
          vZ = v12[7];
        }
        else
        {
          igi2_frame.ptEventContext.tDirection.vX = v11->vX - *(double *)&ptQTask[1].ptNext;
          igi2_frame.ptEventContext.tDirection.vY = v11->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
          vZ = v11->vZ;
        }
        igi2_frame.ptEventContext.tDirection.vZ = vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
        HumanAI_SendEvent(&igi2_frame.ptEventContext);
        igi2_frame.ptEventContext.eEvent = 36;
        igi2_frame.ptEventContext.bFlags = 419;
        igi2_frame.ptEventContext.vRadius = 122880.0;
        HumanAI_SendEvent(&igi2_frame.ptEventContext);
        igi2_frame.ptEventContext.eEvent = 31;
        igi2_frame.ptEventContext.bFlags = 1314;
        igi2_frame.ptEventContext.vRadius = 61440.0;
        HumanAI_SendEvent(&igi2_frame.ptEventContext);
      }
      v20 = igi2_frame.v29 == 0;
      *(_DWORD *)&ptQTask[30].eQTaskType = igi2_frame.v25;
      if ( !v20 )
      {
        igi2_frame.v21 = ptQTask[48].ptParent;
        *(_DWORD *)igi2_frame.v31 = "ai_death_1";
        *(_DWORD *)&igi2_frame.v31[4] = "ai_death_2";
        *(_DWORD *)&igi2_frame.v31[8] = "ai_death_3";
        *(_DWORD *)&igi2_frame.v31[12] = "ai_death_4";
        HumanAI_PlayRandomSoundAtPosition(igi2_frame.v21, 4, (char **)igi2_frame.v31);
      }
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:6425  [anchor-mhash]
void __cdecl HumanSoldier_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptExplosionHitContext; };
    struct { char igi2_o1[24]; _BYTE v18[41]; };
    struct { char igi2_o2[65]; int v19; };
    struct { char igi2_o3[69]; __int16 v20; };
    struct { char igi2_o4[71]; char v21; };
    struct { char igi2_o5[72]; _BYTE v22[29]; };
    struct { char igi2_o6[101]; __int16 v23; };
    struct { char igi2_o7[103]; char v24; };
    struct { char igi2_o8[104]; _BYTE v25[29]; };
    struct { char igi2_o9[133]; __int16 v26; };
    struct { char igi2_o10[135]; char v27; };
    struct { char igi2_o11[136]; _BYTE v28[29]; };
    struct { char igi2_o12[165]; __int16 v29; };
    struct { char igi2_o13[167]; char v30; };
    struct { char igi2_o14[168]; struct real64x3_t ptPos; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // eax
  int v3; // eax
  struct QTask_s *ptTail; // edx
  double *v5; // eax
  double v6; // st7
  double v7; // st6
  long double v8; // st5
  double v9; // st6
  long double v10; // st7
  double v11; // st7
  double v12; // st7
  int v13; // esi
  int v14; // eax
  void (__cdecl *pfHandler)(int, _BYTE *); // ecx
  double v16; // st7

  ptParent = ptQTask[48].ptParent;
  if ( !BYTE1(ptQTask[29].tQTaskRefList.ptHead) || ptParent && BYTE1(ptParent[111].tQTaskChildren.ptMiddle) )
    return;
  v3 = *((_DWORD *)pxContext + 1);
  if ( v3 )
  {
    if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v3 + 36), Human_eQTaskType)
      && *((struct QReference_s **)pxContext + 9) == ptQTask[10].tQTaskRefList.ptTail )
    {
      return;
    }
  }
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  qmemcpy(&igi2_frame.ptPos, &ptTail[10].tQTaskChildren, sizeof(igi2_frame.ptPos));
  v5 = *((double **)pxContext + 3);
  v6 = *v5 - igi2_frame.ptPos.vX;
  v7 = v5[1] - igi2_frame.ptPos.vY;
  *(double *)igi2_frame.v18 = v5[2] - igi2_frame.ptPos.vZ;
  v8 = sqrt(v7 * v7 + *(double *)igi2_frame.v18 * *(double *)igi2_frame.v18 + v6 * v6);
  v9 = *((float *)pxContext + 5) * 3.0;
  if ( v8 - v9 >= 0.0 )
  {
    v10 = 1.0 - (v8 - v9) / (*((float *)pxContext + 5) * 6.0);
    if ( v10 <= 0.0 )
      goto LABEL_11;
  }
  else
  {
    v10 = 1.0;
  }
  *(_DWORD *)igi2_frame.v18 = *((_DWORD *)pxContext + 7);
  ptTail[15].ptNext = (struct QTask_s *)1065353216;
  *(float *)&ptTail[15].ptPrev = 204.8000030517578 * v10;
  *(float *)&ptTail[15].tQTaskChildren.ptHead = v10 * 0.02617993950843811;
  *(float *)&ptTail[15].tQTaskChildren.ptMiddle = 1.0 / (double)*(int *)igi2_frame.v18;
LABEL_11:
  ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)13;
  igi2_frame.ptExplosionHitContext = (sqrt(
                             *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                           + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                           + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
                         + *(float *)&ptQTask[8].ptNext)
                        * 0.3333333432674408;
  v11 = GameFunctions_ResolveExplosionHit(
          (struct ExplosionHitContext_t *)pxContext,
          ptQTask,
          &igi2_frame.ptPos,
          igi2_frame.ptExplosionHitContext,
          true);
  if ( v11 != 0.0 )
  {
    v12 = v11 * *(float *)&ptQTask[28].tQTaskRefList.ptHead;
    *(float *)&ptQTask[28].tQTaskChildren.ptTail = v12 + *(float *)&ptQTask[28].tQTaskChildren.ptTail;
    *(float *)&ptQTask[25].tQTaskRefList.ptHead = v12 + *(float *)&ptQTask[25].tQTaskRefList.ptHead;
    v13 = *(_DWORD *)&ptQTask[30].eQTaskType;
    *(float *)&ptQTask[75].tQTaskChildren.ptMiddle = v12 + *(float *)&ptQTask[75].tQTaskChildren.ptMiddle;
    if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
    {
      v14 = *((_DWORD *)pxContext + 1);
      if ( v14 )
      {
        *(_DWORD *)igi2_frame.v18 = ptQTask;
        pfHandler = (void (__cdecl *)(int, _BYTE *))QTask_aatQTaskFinalEvent[Human_eKilledByYouQTaskEvent][*(unsigned __int16 *)(v14 + 36)].pfHandler;
        if ( pfHandler )
          pfHandler(v14, igi2_frame.v18);
      }
      v16 = *(double *)&ptQTask[1].ptNext;
      ptQTask[76].ptNext = nullptr;
      *(float *)&ptQTask[50].tQTaskRefList.ptHead = v16 - *(double *)*((_DWORD *)pxContext + 3);
      *(float *)&ptQTask[50].tQTaskRefList.ptMiddle = *(double *)&ptQTask[1].tQTaskChildren.ptHead
                                                    - *(double *)(*((_DWORD *)pxContext + 3) + 8);
      *(float *)&ptQTask[50].tQTaskRefList.ptTail = *(double *)&ptQTask[1].tQTaskChildren.ptTail
                                                  - *(double *)(*((_DWORD *)pxContext + 3) + 16);
      ptQTask[76].ptPrev = *((struct QTask_s **)pxContext + 4);
      LOBYTE(ptQTask[29].tQTaskRefList.ptHead) = 1;
      *(_DWORD *)&ptQTask[30].eQTaskType = v13 | 0x20000;
    }
    else
    {
      strcpy(&igi2_frame.v18[16], "GV_69_03");
      memset(&igi2_frame.v18[25], 0, 16);
      igi2_frame.v19 = 0;
      igi2_frame.v20 = 0;
      igi2_frame.v21 = 0;
      strcpy(igi2_frame.v22, "GV_70_03");
      strcpy(igi2_frame.v25, "GV_71_03");
      memset(&igi2_frame.v22[9], 0, 20);
      memset(&igi2_frame.v25[9], 0, 20);
      strcpy(igi2_frame.v28, "GV_72_03");
      memset(&igi2_frame.v28[9], 0, 20);
      igi2_frame.v23 = 0;
      igi2_frame.v24 = 0;
      igi2_frame.v26 = 0;
      igi2_frame.v27 = 0;
      igi2_frame.v29 = 0;
      *(_DWORD *)&igi2_frame.v18[4] = igi2_frame.v22;
      igi2_frame.v30 = 0;
      *(_DWORD *)igi2_frame.v18 = &igi2_frame.v18[16];
      *(_DWORD *)&igi2_frame.v18[8] = igi2_frame.v25;
      *(_DWORD *)&igi2_frame.v18[12] = igi2_frame.v28;
      Human_HitSound(ptQTask, (char **)igi2_frame.v18, 4);
      *(_DWORD *)&ptQTask[30].eQTaskType = v13 | 0x10000;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:6628  [anchor-mhash]
void __cdecl HumanSoldier_CloseCombatDamageHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { long double v16; };
    struct { char igi2_o1[8]; double v17; };
    struct { char igi2_o2[24]; struct HumanAIEventContext_t v18; };
    struct { char igi2_o3[88]; _BYTE v19[29]; };
    struct { char igi2_o4[117]; __int16 v20; };
    struct { char igi2_o5[119]; char v21; };
    struct { char igi2_o6[120]; _BYTE v22[29]; };
    struct { char igi2_o7[149]; __int16 v23; };
    struct { char igi2_o8[151]; char v24; };
    struct { char igi2_o9[152]; double v25; };
    struct { char igi2_o10[160]; double v26; };
    struct { char igi2_o11[168]; double v27; };
    char igi2_extent[176];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // eax
  double *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v6; // st3
  long double v7; // st7
  int v8; // eax
  double v9; // st6
  int v10; // ebx
  int v11; // ebx
  long double v12; // st6
  struct QTask_s *v13; // eax
  __int16 v14; // ax
  struct QTask_s *v15; // edi

  ptParent = ptQTask[48].ptParent;
  if ( !ptParent || !BYTE1(ptParent[111].tQTaskChildren.ptMiddle) )
  {
    v3 = *((double **)pxContext + 1);
    igi2_frame.v25 = (*(float *)&ptQTask[3].tQTaskChildren.ptMiddle + *(float *)&ptQTask[3].ptPrev) * 0.0
        + *(float *)&ptQTask[3].tQTaskChildren.ptHead * 4096.0;
    igi2_frame.v26 = (*(float *)&ptQTask[3].tQTaskRefList.ptMiddle + *(float *)&ptQTask[3].tQTaskChildren.ptTail) * 0.0
        + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 4096.0;
    igi2_frame.v27 = (*(float *)&ptQTask[3].eQTaskType + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0
        + *(float *)&ptQTask[3].ptParent * 4096.0;
    v4 = *(double *)&ptQTask[1].ptNext - v3[5];
    igi2_frame.v17 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - v3[6];
    v5 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - v3[7];
    v6 = 1.0 / sqrt(igi2_frame.v17 * igi2_frame.v17 + v5 * v5 + v4 * v4);
    igi2_frame.v16 = v6 * v4;
    igi2_frame.v17 = igi2_frame.v17 * v6;
    v7 = v6 * v5;
    v8 = 14;
    if ( igi2_frame.v27 * v7 + igi2_frame.v17 * igi2_frame.v26 + igi2_frame.v16 * igi2_frame.v25 < 0.0 )
      v8 = 13;
    ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)v8;
    v9 = *((float *)&ptQTask[25].eQTaskType + 2 * v8) * *(float *)pxContext;
    *((float *)&ptQTask[25].ptParent + 2 * v8) = v9 + *((float *)&ptQTask[25].ptParent + 2 * v8);
    *(float *)&ptQTask[25].tQTaskRefList.ptHead = v9 + *(float *)&ptQTask[25].tQTaskRefList.ptHead;
    v10 = *(_DWORD *)&ptQTask[30].eQTaskType;
    *(float *)&ptQTask[75].tQTaskChildren.ptMiddle = v9 + *(float *)&ptQTask[75].tQTaskChildren.ptMiddle;
    if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
    {
      v12 = igi2_frame.v16;
      ptQTask[76].ptNext = (struct QTask_s *)4;
      *(float *)&ptQTask[50].tQTaskRefList.ptHead = v12;
      v11 = v10 | 0x20000;
      *(float *)&ptQTask[50].tQTaskRefList.ptMiddle = igi2_frame.v17;
      *(float *)&ptQTask[50].tQTaskRefList.ptTail = v7;
      ptQTask[76].ptPrev = *(struct QTask_s **)pxContext;
      LOBYTE(ptQTask[29].tQTaskRefList.ptHead) = 1;
    }
    else
    {
      strcpy((char *)&igi2_frame.v18, "GV_69_03");
      memset((char *)&igi2_frame.v18.bFlags + 1, 0, 23);
      strcpy((char *)&igi2_frame.v18.ptReferenceQTask, "GV_70_03");
      strcpy(igi2_frame.v19, "GV_71_03");
      memset((char *)&igi2_frame.v18.uEventSpecificData.tEnemyDetection.iIndex + 1, 0, 23);
      memset(&igi2_frame.v19[9], 0, 20);
      strcpy(igi2_frame.v22, "GV_72_03");
      memset(&igi2_frame.v22[9], 0, 20);
      igi2_frame.v20 = 0;
      igi2_frame.v21 = 0;
      igi2_frame.v23 = 0;
      HIDWORD(igi2_frame.v16) = &igi2_frame.v18.ptReferenceQTask;
      igi2_frame.v24 = 0;
      LODWORD(igi2_frame.v16) = &igi2_frame.v18;
      LODWORD(igi2_frame.v17) = igi2_frame.v19;
      HIDWORD(igi2_frame.v17) = igi2_frame.v22;
      v11 = v10 | 0x10000;
      Human_HitSound(ptQTask, (char **)&igi2_frame.v16, 4);
    }
    *(_DWORD *)&ptQTask[30].eQTaskType = v11;
  }
  v13 = *((struct QTask_s **)pxContext + 1);
  igi2_frame.v18.eTeam = 1;
  igi2_frame.v18.ptReferenceQTask = v13;
  igi2_frame.v18.ptHumanOriginatorQTask = v13;
  igi2_frame.v18.eEvent = 31;
  igi2_frame.v18.bFlags = 1314;
  igi2_frame.v18.vRadius = 61440.0;
  igi2_frame.v18.ptPosition = (struct real64x3_t *)&ptQTask[1];
  HumanAI_SendEvent(&igi2_frame.v18);
  v14 = HumanAI_eSendEventQTaskEvent;
  v15 = ptQTask[48].ptParent;
  if ( HumanAI_eSendEventQTaskEvent == 512 )
  {
    v14 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
    HumanAI_eSendEventQTaskEvent = v14;
  }
  ((void (__cdecl *)(struct QTask_s *, struct HumanAIEventContext_t *))QTask_aatQTaskFinalEvent[v14][v15->eQTaskType].pfHandler)(
    v15,
    &igi2_frame.v18);
}

// source: j/0/human/soldiertypes/humansoldier.c:6779  [anchor-mhash]
void __cdecl HumanSoldier_FlashBangHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct real64x3_t *v2; // edx
  double v3; // st7
  double v4; // st6
  double v5; // st5
  float v6; // edx
  struct QTask_s *ptParent; // esi
  struct HumanAIEventContext_t tEventContext; // [esp+4h] [ebp-40h] BYREF

  v2 = *(struct real64x3_t **)pxContext;
  v3 = *(double *)*(_DWORD *)pxContext - *(double *)&ptQTask[1].ptNext;
  v4 = *(double *)(*(_DWORD *)pxContext + 8) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  v5 = *(double *)(*(_DWORD *)pxContext + 16) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  if ( sqrt(v3 * v3 + v4 * v4 + v5 * v5) <= *((float *)pxContext + 1)
    && v5 * *(float *)&ptQTask[3].ptParent
     + v4 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
     + v3 * *(float *)&ptQTask[3].tQTaskChildren.ptHead >= 0.0 )
  {
    tEventContext.eTeam = *((_DWORD *)pxContext + 2);
    tEventContext.ptHumanOriginatorQTask = nullptr;
    tEventContext.ptReferenceQTask = nullptr;
    tEventContext.ptPosition = v2;
    v6 = *((float *)pxContext + 1);
    ptParent = ptQTask[48].ptParent;
    tEventContext.bFlags = 67;
    tEventContext.eEvent = 18;
    tEventContext.vRadius = v6;
    HumanAI_SendEventSpecificQTask(ptParent, &tEventContext);
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:6838  [anchor-mhash]
void __cdecl HumanSoldier_GetShadowInfoHandler(struct QTask_s *ptQTask, void *pxData)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v9; };
    struct { char igi2_o1[4]; struct real64x3_t a1; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int *ptParent; // edi
  struct Graph_s *v3; // esi
  int v4; // eax
  _DWORD *v5; // eax
  BOOL v6; // ecx
  int v7; // ecx
  long double v8; // st7

  ptParent = (int *)ptQTask[48].ptParent;
  igi2_frame.v9 = 0;
  if ( ptParent )
  {
    v3 = (struct Graph_s *)ptParent[7282];
    if ( v3 )
    {
      if ( !ptParent[124] )
      {
        v4 = ptParent[7487];
LABEL_7:
        if ( !Graph_GetNode(v3, v4)->ptSectorQTask )
          goto LABEL_9;
        goto LABEL_8;
      }
      if ( !Graph_GetNode(v3, ptParent[122])->ptSectorQTask )
      {
        v4 = ptParent[123];
        v3 = (struct Graph_s *)ptParent[7282];
        goto LABEL_7;
      }
    }
  }
LABEL_8:
  igi2_frame.v9 = 1;
LABEL_9:
  v5 = pxData;
  *((_DWORD *)pxData + 4) = ptQTask;
  if ( igi2_frame.v9 )
  {
    *((_DWORD *)pxData + 3) = 0;
    *(_DWORD *)&ptQTask[47].eQTaskType = !ptQTask[48].ptNext || HIBYTE(ptQTask[50].ptNext) && !ptQTask[48].ptPrev;
  }
  else
  {
    v6 = HIBYTE(ptQTask[50].ptNext) && !ptQTask[48].ptPrev;
    *(_DWORD *)&ptQTask[47].eQTaskType = v6;
    v7 = *((_DWORD *)pxData + 2);
    *((_DWORD *)pxData + 3) = 1;
    if ( v7 )
    {
      if ( !ptQTask[47].ptParent )
      {
        qmemcpy(&igi2_frame.a1, &ptQTask[1], sizeof(igi2_frame.a1));
        igi2_frame.a1.vZ = igi2_frame.a1.vZ + 7372.8;
        v8 = sub_5C5840(&igi2_frame.a1, Game_ptGame->ptWorld, 204800.0);
        v5 = pxData;
        *(float *)&ptQTask[48].tQTaskChildren.ptMiddle = v8 + 6144.0;
      }
      v5[1] = ptQTask[48].tQTaskChildren.ptMiddle;
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:6910  [anchor-mhash]
void __cdecl HumanSoldier_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct CollisionEvaluateContext_s ptEvalContext; };
    struct { char igi2_o1[8]; struct CollisionEvaluateContext_s v8; };
    struct { char igi2_o2[16]; int v9; };
    struct { char igi2_o3[20]; struct QTask_s *v10; };
    struct { char igi2_o4[32]; struct real64x3_t ptEnd; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st7
  int v6; // eax

  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
  {
    if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) && ptQTask[10].tQTaskRefList.ptTail == (struct QReference_s *)1 )
    {
      sub_580CA0((int)ptQTask, &igi2_frame.ptEnd.vX);
      v2 = *((double *)pxContext + 1) - igi2_frame.ptEnd.vX;
      v3 = *((double *)pxContext + 2) - igi2_frame.ptEnd.vY;
      v4 = *((double *)pxContext + 3) - igi2_frame.ptEnd.vZ;
      *(double *)&igi2_frame.v8 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * v4
                     + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v3
                     + *(float *)&ptQTask[3].ptPrev * v2;
      if ( *(float *)&ptQTask[3].ptParent * v4
         + *(float *)&ptQTask[3].tQTaskRefList.ptHead * v3
         + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v2 < 0.0 )
      {
        v5 = *(double *)&igi2_frame.v8;
        if ( *(double *)&igi2_frame.v8 < 0.0 )
          v5 = -*(double *)&igi2_frame.v8;
        if ( v5 < 3072.0 )
        {
          v6 = *(_DWORD *)pxContext;
          igi2_frame.v8.ptQTask = nullptr;
          igi2_frame.v9 = v6;
          igi2_frame.v10 = ptQTask;
          if ( World_LineOfSight(
                 Game_ptGame->ptWorld,
                 (struct real64x3_t *)((char *)pxContext + 8),
                 &igi2_frame.ptEnd,
                 AIDetection_eLineOfSightQTaskEvent,
                 &igi2_frame.v8,
                 Forest_bQTaskGroup | 0x8000000,
                 WORLD_DYNCUBETREE_CATEGORY_ALL,
                 (struct LineOfSightOutputContext_s *)&igi2_frame.ptEvalContext) )
          {
            GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &igi2_frame.ptEnd);
          }
        }
      }
    }
  }
}

// source: j/0/human/soldiertypes/humansoldier.c:6950  [size]
void __cdecl HumanSoldier_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 13;
}

// source: j/0/human/soldiertypes/humansoldier.c:6967  [size]
void __cdecl HumanSoldier_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/human/soldiertypes/humansoldier.c:6987  [size]
void __cdecl HumanSoldier_DrawActionItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ActionMenuScreen_DrawActionItem(
    ActionMenuScreen_ptQTask,
    (struct QSprite_s *)&StatusScreen_ptStatusScreenQTask[26].tQTaskRefList,
    pxContext);
}

// source: j/0/human/soldiertypes/humansoldier.c:7005  [anchor-strings]
void __cdecl HumanSoldier_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  unsigned __int16 v2; // si

  HumanSoldier_InitAnimStateIndexes();
  HumanSoldier_InitStateFunctions();
  v0 = QTask_NewQTaskType("HumanSoldier", 3064, Human_eQTaskType, 0, 0);
  HumanSoldier_eQTaskType = v0;
  QTask_SetQTaskTypeGroup(v0, 1u);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, HumanSoldier_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, HumanSoldier_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, RunDelayed_eQTaskEvent, HumanSoldier_RunDelayedHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    HumanSoldier_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, HumanSoldier_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanSoldier_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, HumanSoldier_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ShadowVolume_eGetShadowInfoEvent, HumanSoldier_GetShadowInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 12, nullptr);
  v1 = Human_eHumanUpdateQTaskEvent;
  if ( Human_eHumanUpdateQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, "HumanUpdate");
    v0 = HumanSoldier_eQTaskType;
    Human_eHumanUpdateQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, HumanSoldier_HumanUpdateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, HumanSoldier_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, HumanSoldier_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Human_eCloseCombatDamageQTaskEvent, HumanSoldier_CloseCombatDamageHandler);
  QTask_LinkQTaskEventHandlerFn(v0, FlashBang_eFlashBangQTaskEvent, HumanSoldier_FlashBangHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimTrigger_eTriggerAnimTriggerQTaskEvent, HumanSoldier_TriggerAnimTriggerHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Weapon_eGetParentParametersQTaskEvent,
    HumanSoldier_WeaponGetParentParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 4, (void (__cdecl *)(struct QTask_s *, void *))HumanSoldier_ParentChangedQTaskEvent);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eEvaluateActivateQTaskEvent, HumanSoldier_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanSoldier_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanSoldier_ActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ActionMenuScreen_eDrawActionItemQTaskEvent, HumanSoldier_DrawActionItemHandler);
  Symbol_Register(
    "TASKTYPE_HUMANSOLDIER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  HumanSoldier_ptParameterList = ParameterList_Derive(Human_ptParameterList, 2);
  ParameterList_AddParameter(
    HumanSoldier_ptParameterList,
    0xBB4u,
    Level_eParameterTypeInt32,
    "Bone Heirachy",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanSoldier_ptParameterList,
    0xBB8u,
    Level_eParameterTypeInt32,
    "Stand Animation",
    7u,
    nullptr);
  v2 = HumanSoldier_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    HumanSoldier_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanSoldier_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v2, Serialize_eDeSerializeQTaskEvent, HumanSoldier_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    Serialize_eSerializeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanSoldier_SerializeHandler);
  HumanSoldier_ptSerializeParameterList = ParameterList_Derive(Human_ptSerializeParameterList, 4);
  ParameterList_AddParameter(
    HumanSoldier_ptSerializeParameterList,
    0x588u,
    Level_eParameterTypeInt32,
    "iStateLastUsedToSetMainAnimation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanSoldier_ptSerializeParameterList,
    0xBD8u,
    Level_eParameterTypeInt32,
    "abSeenDeadBySquadBitField0",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanSoldier_ptSerializeParameterList,
    0xBDCu,
    Level_eParameterTypeInt32,
    "abSeenDeadBySquadBitField1",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanSoldier_ptSerializeParameterList,
    0xBD5u,
    Level_eParameterTypebool8,
    "isSeenDeadByCamera",
    7u,
    nullptr);
  HumanSoldier_ptUpdateProfileRegion = nullptr;
  HumanSoldier_ptHumanAnimUpdate = nullptr;
  HumanSoldier_ptMaintainUpperBodyStateRegion = nullptr;
  HumanSoldier_ptHumanViewUpdateBodyProfileRegion = nullptr;
  HumanSoldier_ptHumanViewUpdateViewProfileRegion = nullptr;
  HumanSoldier_ptMoveProfileRegion = nullptr;
  HumanSoldier_ptWeaponUpdateStatusProfileRegion = nullptr;
  HumanSoldier_ptNotifyProfileRegion = nullptr;
  HumanSoldier_ptUpdateFeetSoundProfileRegion = nullptr;
  HumanSoldier_ptStateRunProfileRegion = nullptr;
  HumanSoldier_ptUpdateBodyProfileRegion = nullptr;
  HumanSoldier_InitAnimStateIndexes();
}

// source: j/0/human/soldiertypes/humansoldier.c:7098  [size]
void __cdecl HumanSoldier_Close()
{
  int v0; // esi
  int v1; // esi

  if ( HumanSoldier_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&HumanSoldier_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( HumanSoldier_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&HumanSoldier_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(HumanSoldier_eQTaskType);
}

// source: j/0/human/soldiertypes/humansoldier.c:7117  [size]
unsigned __int16 __cdecl HumanSoldier_GetQTaskType()
{
  return HumanSoldier_eQTaskType;
}

// source: j/0/human/soldiertypes/humansoldier.c:7131  [anchor-mhash]
enum bool __cdecl HumanSoldier_FindCollisionDirectionAndTurn(
        struct QTask_s *ptQTask,
        struct real32x3_t *ptImpactDirection)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v14; };
    struct { char igi2_o1[40]; struct real32x3_t tNormalizedImpactDirection; };
    struct { char igi2_o2[52]; struct real32x3_t Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o3[64]; struct real64x3_t tReal64x3; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char v2; // bl
  long double vX; // st7
  float vY; // eax
  float vZ; // ecx
  long double v7; // st6
  double v8; // st6
  double v9; // st5
  double v10; // st4
  double v11; // st3
  double v12; // st2
  double v13; // st7

  v2 = 0;
  if ( ptImpactDirection->vX == 0.0 && ptImpactDirection->vY == 0.0 && ptImpactDirection->vZ == 0.0 )
    return true;
  igi2_frame.tNormalizedImpactDirection.vX = ptImpactDirection->vX;
  vX = igi2_frame.tNormalizedImpactDirection.vX;
  vY = ptImpactDirection->vY;
  vZ = ptImpactDirection->vZ;
  igi2_frame.tNormalizedImpactDirection.vY = vY;
  igi2_frame.tNormalizedImpactDirection.vZ = vZ;
  if ( igi2_frame.tNormalizedImpactDirection.vX != 0.0
    || igi2_frame.tNormalizedImpactDirection.vY != 0.0
    || igi2_frame.tNormalizedImpactDirection.vZ != 0.0 )
  {
    v7 = 1.0
       / sqrt(
           vX * vX
         + igi2_frame.tNormalizedImpactDirection.vY * igi2_frame.tNormalizedImpactDirection.vY
         + igi2_frame.tNormalizedImpactDirection.vZ * igi2_frame.tNormalizedImpactDirection.vZ);
    vX = igi2_frame.tNormalizedImpactDirection.vX * v7;
    igi2_frame.tNormalizedImpactDirection.vY = igi2_frame.tNormalizedImpactDirection.vY * v7;
    igi2_frame.tNormalizedImpactDirection.vZ = igi2_frame.tNormalizedImpactDirection.vZ * v7;
  }
  v8 = (*(float *)&ptQTask[3].tQTaskChildren.ptMiddle + *(float *)&ptQTask[3].ptPrev) * 0.0
     + *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  v9 = (*(float *)&ptQTask[3].tQTaskRefList.ptMiddle + *(float *)&ptQTask[3].tQTaskChildren.ptTail) * 0.0
     + *(float *)&ptQTask[3].tQTaskRefList.ptHead;
  v10 = (*(float *)&ptQTask[3].eQTaskType + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0
      + *(float *)&ptQTask[3].ptParent;
  v11 = igi2_frame.tNormalizedImpactDirection.vY * *(float *)&ptQTask[3].tQTaskChildren.ptTail
      + igi2_frame.tNormalizedImpactDirection.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail
      + vX * *(float *)&ptQTask[3].ptPrev;
  v12 = igi2_frame.tNormalizedImpactDirection.vZ * *(float *)&ptQTask[3].ptParent
      + vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead
      + igi2_frame.tNormalizedImpactDirection.vY * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
  igi2_frame.Real32x3_RotateInverse_tTemp.vZ = igi2_frame.tNormalizedImpactDirection.vY * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                  + vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                  + igi2_frame.tNormalizedImpactDirection.vZ * *(float *)&ptQTask[3].eQTaskType;
  igi2_frame.tReal64x3.vX = v11;
  igi2_frame.tReal64x3.vY = v12;
  igi2_frame.tReal64x3.vZ = igi2_frame.Real32x3_RotateInverse_tTemp.vZ;
  qmemcpy(&igi2_frame.v14, &igi2_frame.tReal64x3, sizeof(igi2_frame.v14));
  if ( igi2_frame.tNormalizedImpactDirection.vZ * v10 + v9 * igi2_frame.tNormalizedImpactDirection.vY + v8 * vX <= 0.0 )
  {
    v2 = 1;
    v13 = GameFunctions_CalcGamma(igi2_frame.v14) + 3.1415927410125732;
  }
  else
  {
    v13 = GameFunctions_CalcGamma(igi2_frame.v14);
  }
  *(float *)&ptQTask[19].ptPrev = v13;
  *(float *)&ptQTask[19].ptPrev = *(float *)&ptQTask[19].ptPrev * -0.31830987334251404;
  return v2;
}

// source: j/0/human/soldiertypes/humansoldier.c:7201  [anchor-callee]
struct QTask_s *__cdecl HumanSoldier_GetCheapHeadBonePosition(
        struct QTask_s *ptQTask,
        struct real32x3_t *ptLocalPosition,
        struct real64x3_t *ptWorldPosition)
{
  struct QTask_s *ptPrev; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  float tReal32x3_8; // [esp+Ch] [ebp-4h]

  ptPrev = ptQTask[31].ptPrev;
  if ( ptPrev == (struct QTask_s *)27
    || ptPrev == (struct QTask_s *)32
    || ptPrev == (struct QTask_s *)33
    || ptPrev == (struct QTask_s *)34
    || ptPrev == (struct QTask_s *)35
    || ptPrev == (struct QTask_s *)20 )
  {
    if ( ptLocalPosition )
    {
      ptLocalPosition->vX = -409.6000061035156;
      ptLocalPosition->vY = 0.0;
      ptLocalPosition->vZ = 4915.2001953125;
    }
    if ( ptWorldPosition )
    {
      v4 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 4915.2001953125
         + *(float *)&ptQTask[3].tQTaskChildren.ptHead * 0.0
         - *(float *)&ptQTask[3].ptPrev * 409.6000061035156;
      v5 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 4915.2001953125
         + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 0.0
         - *(float *)&ptQTask[3].tQTaskChildren.ptTail * 409.6000061035156;
      v6 = *(float *)&ptQTask[3].eQTaskType * 4915.2001953125
         + *(float *)&ptQTask[3].ptParent * 0.0
         - *(float *)&ptQTask[3].tQTaskRefList.ptTail * 409.6000061035156;
      goto LABEL_23;
    }
  }
  else if ( ptPrev == (struct QTask_s *)36
         || ptPrev == (struct QTask_s *)37
         || ptPrev == (struct QTask_s *)38
         || ptPrev == (struct QTask_s *)22 )
  {
    if ( ptLocalPosition )
    {
      ptLocalPosition->vX = 0.0;
      ptLocalPosition->vY = 8192.0;
      ptLocalPosition->vZ = 1228.800048828125;
    }
    if ( ptWorldPosition )
    {
      v4 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 1228.800048828125
         + *(float *)&ptQTask[3].tQTaskChildren.ptHead * 8192.0
         + *(float *)&ptQTask[3].ptPrev * 0.0;
      v5 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 1228.800048828125
         + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 8192.0
         + *(float *)&ptQTask[3].tQTaskChildren.ptTail * 0.0;
      v6 = *(float *)&ptQTask[3].eQTaskType * 1228.800048828125
         + *(float *)&ptQTask[3].ptParent * 8192.0
         + *(float *)&ptQTask[3].tQTaskRefList.ptTail * 0.0;
      goto LABEL_23;
    }
  }
  else
  {
    if ( ptLocalPosition )
    {
      ptLocalPosition->vX = 0.0;
      ptLocalPosition->vY = 0.0;
      ptLocalPosition->vZ = 6758.39990234375;
    }
    if ( ptWorldPosition )
    {
      v4 = (*(float *)&ptQTask[3].tQTaskChildren.ptHead + *(float *)&ptQTask[3].ptPrev) * 0.0
         + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 6758.39990234375;
      v5 = (*(float *)&ptQTask[3].tQTaskRefList.ptHead + *(float *)&ptQTask[3].tQTaskChildren.ptTail) * 0.0
         + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 6758.39990234375;
      v6 = (*(float *)&ptQTask[3].ptParent + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0
         + *(float *)&ptQTask[3].eQTaskType * 6758.39990234375;
LABEL_23:
      tReal32x3_8 = v6;
      ptWorldPosition->vX = v4 + *(double *)&ptQTask[1].ptNext;
      ptWorldPosition->vY = v5 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
      ptWorldPosition->vZ = tReal32x3_8 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    }
  }
  return ptQTask;
}

// source: j/0/human/soldiertypes/humansoldier.c:7282  [anchor-mhash]
struct QTask_s *__cdecl HumanSoldier_GetCheapCenterBonePosition(
        struct QTask_s *ptQTask,
        struct real32x3_t *ptLocalPosition,
        struct real64x3_t *ptWorldPosition)
{
  struct QTask_s *ptPrev; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st4
  float tReal32x3_8; // [esp+Ch] [ebp-4h]

  ptPrev = ptQTask[31].ptPrev;
  if ( ptPrev == (struct QTask_s *)27
    || ptPrev == (struct QTask_s *)32
    || ptPrev == (struct QTask_s *)33
    || ptPrev == (struct QTask_s *)34
    || ptPrev == (struct QTask_s *)35
    || ptPrev == (struct QTask_s *)20 )
  {
    if ( ptLocalPosition )
    {
      ptLocalPosition->vX = 0.0;
      ptLocalPosition->vY = 0.0;
      ptLocalPosition->vZ = 1638.4000244140625;
    }
    if ( ptWorldPosition )
    {
      v4 = (*(float *)&ptQTask[3].tQTaskChildren.ptHead + *(float *)&ptQTask[3].ptPrev) * 0.0
         + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 1638.4000244140625;
      v5 = (*(float *)&ptQTask[3].tQTaskRefList.ptHead + *(float *)&ptQTask[3].tQTaskChildren.ptTail) * 0.0
         + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 1638.4000244140625;
      v6 = (*(float *)&ptQTask[3].ptParent + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0;
      v7 = *(float *)&ptQTask[3].eQTaskType * 1638.4000244140625;
      goto LABEL_23;
    }
  }
  else if ( ptPrev == (struct QTask_s *)36
         || ptPrev == (struct QTask_s *)37
         || ptPrev == (struct QTask_s *)38
         || ptPrev == (struct QTask_s *)22 )
  {
    if ( ptLocalPosition )
    {
      ptLocalPosition->vX = 0.0;
      ptLocalPosition->vY = 0.0;
      ptLocalPosition->vZ = 819.2000122070312;
    }
    if ( ptWorldPosition )
    {
      v4 = (*(float *)&ptQTask[3].tQTaskChildren.ptHead + *(float *)&ptQTask[3].ptPrev) * 0.0
         + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 819.2000122070312;
      v5 = (*(float *)&ptQTask[3].tQTaskRefList.ptHead + *(float *)&ptQTask[3].tQTaskChildren.ptTail) * 0.0
         + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 819.2000122070312;
      v6 = (*(float *)&ptQTask[3].ptParent + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0;
      v7 = *(float *)&ptQTask[3].eQTaskType * 819.2000122070312;
      goto LABEL_23;
    }
  }
  else
  {
    if ( ptLocalPosition )
    {
      ptLocalPosition->vX = 0.0;
      ptLocalPosition->vY = 0.0;
      ptLocalPosition->vZ = 4096.0;
    }
    if ( ptWorldPosition )
    {
      v4 = (*(float *)&ptQTask[3].tQTaskChildren.ptHead + *(float *)&ptQTask[3].ptPrev) * 0.0
         + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 4096.0;
      v5 = (*(float *)&ptQTask[3].tQTaskRefList.ptHead + *(float *)&ptQTask[3].tQTaskChildren.ptTail) * 0.0
         + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 4096.0;
      v6 = (*(float *)&ptQTask[3].ptParent + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0;
      v7 = *(float *)&ptQTask[3].eQTaskType * 4096.0;
LABEL_23:
      tReal32x3_8 = v6 + v7;
      ptWorldPosition->vX = v4 + *(double *)&ptQTask[1].ptNext;
      ptWorldPosition->vY = v5 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
      ptWorldPosition->vZ = tReal32x3_8 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    }
  }
  return ptQTask;
}

// source: j/0/human/soldiertypes/humansoldier.c:7359  [size]
void __cdecl HumanSoldier_SetMovementSpeedScale(
        struct QTask_s *ptQTask,
        float vMovementSpeedScale)
{
  *(float *)&ptQTask[75].tQTaskChildren.ptTail = vMovementSpeedScale;
}

// source: j/0/human/soldiertypes/humansoldier.c:7380  [size]
struct QTask_s *__cdecl HumanSoldier_GetCurrentSectorQTask(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax

  ptParent = ptQTask[48].ptParent;
  if ( ptParent )
    return (struct QTask_s *)ptParent[725].tQTaskRefList.ptTail;
  else
    return nullptr;
}

// source: j/0/human/soldiertypes/humansoldier.c:7406  [size]
enum WeaponTypeAnim_e __cdecl HumanSoldier_GetWeaponTypeAnimFromState(int eState)
{
  return HumanSoldier_atStateData[eState].iWeaponTypeAnim;
}

BOOL __cdecl sub_4F8050(int a1, int a2)
{
  int v2; // ecx
  _DWORD *v3; // edx

  v2 = *(_DWORD *)(a2 + 8656);
  if ( v2 < 32 )
  {
    v3 = (_DWORD *)(a1 + 3032);
    return (*v3 & (1 << v2)) != 0;
  }
  if ( v2 < 64 )
  {
    v3 = (_DWORD *)(a1 + 3036);
    LOBYTE(v2) = v2 - 32;
    return (*v3 & (1 << v2)) != 0;
  }
  return 0;
}

_DWORD *__cdecl sub_4F8090(_DWORD *result, int a2)
{
  int v2; // ecx

  v2 = *(_DWORD *)(a2 + 8656);
  if ( v2 >= 32 )
  {
    if ( v2 < 64 )
    {
      result += 759;
      *result |= 1 << (v2 - 32);
    }
  }
  else
  {
    result += 758;
    *result |= 1 << v2;
  }
  return result;
}
