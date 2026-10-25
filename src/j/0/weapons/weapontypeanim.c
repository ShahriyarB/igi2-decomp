/* j/0/weapons/weapontypeanim.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/weapontypeanim.c:71  [anchor-mhash]
void __cdecl WeaponTypeAnim_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  memset(&ptQTask[1], 0, 0x3BCu);
  *(_DWORD *)&ptQTask[24].eQTaskType = 0;
}

// source: j/0/weapons/weapontypeanim.c:97  [size]
void __cdecl WeaponTypeAnim_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/weapontypeanim.c:112  [size]
void __cdecl WeaponTypeAnim_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/weapontypeanim.c:127  [size]
void __cdecl WeaponTypeAnim_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/weapontypeanim.c:145  [size]
void __cdecl WeaponTypeAnim_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = WeaponTypeAnim_ptParameterList;
}

// source: j/0/weapons/weapontypeanim.c:162  [anchor-hash]
void __cdecl WeaponTypeAnim_InitBaseAnimNameTable()
{
  strcpy(WeaponTypeAnim_azBaseAnimName, "stand");
  strcpy(&WeaponTypeAnim_azBaseAnimName[32], "stand_turn_mp_shuffle");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[64], "stand_lowerb", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[76] = (char *)&MTP_atLODVirModel[1].atBoneVertexRefs[18].atVertexRefs[362].iVertex
                                                + 3;
  strcpy(&WeaponTypeAnim_azBaseAnimName[96], "civilian_walk");
  strcpy(&WeaponTypeAnim_azBaseAnimName[128], "stand_run_fwd_full");
  strcpy(&WeaponTypeAnim_azBaseAnimName[192], "stand_run_left");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[224], "stand_run_ri", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[236] = (char *)&HumanAI_atMovementQueueItems[786].nNodeID + 3;
  strcpy(&WeaponTypeAnim_azBaseAnimName[160], "stand_run_forward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[256], "stand_run_forward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[288], "stand_run_forward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[320], "stand_run_backward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[352], "stand_run_backward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[384], "stand_run_backward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[416], "stand_walk_forward");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[448], "stand_walk_l", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[460] = (char *)&HumanAI_atMovementQueueItems[776].tNode.ptPrev + 1;
  strcpy(&WeaponTypeAnim_azBaseAnimName[480], "stand_walk_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[512], "stand_walk_forward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[544], "stand_walk_forward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[576], "stand_walk_backward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[608], "stand_walk_backward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[640], "stand_walk_backward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[672], "stand_fire_stationarygun");
  strcpy(&WeaponTypeAnim_azBaseAnimName[704], "stand_roll_left_to_kneel");
  strcpy(&WeaponTypeAnim_azBaseAnimName[736], "stand_roll_right_to_kneel");
  strcpy(&WeaponTypeAnim_azBaseAnimName[768], "stand_to_kneel");
  strcpy(&WeaponTypeAnim_azBaseAnimName[800], "stand_to_flat");
  strcpy(&WeaponTypeAnim_azBaseAnimName[832], "stand_run_panick");
  strcpy(&WeaponTypeAnim_azBaseAnimName[864], "stand_kick_grenade");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[896], "stand_al", 8);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[904] = (char *)&HumanAI_atMovementQueueItems[840].tNode.ptPrev + 1;
  strcpy(&WeaponTypeAnim_azBaseAnimName[928], "stand_look_about_stunned");
  strcpy(&WeaponTypeAnim_azBaseAnimName[960], "stand_flashbang_stunned");
  strcpy(&WeaponTypeAnim_azBaseAnimName[992], "stand_salute");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1024], "stand_talk1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1056], "stand_talk2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1088], "stand_bugged_by_fly");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1120], "stand_clean_weapon");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1152], "stand_sneze");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1184], "stand_wipe_nose");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1216], "stand_streatch_neck");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1248], "stand_scratch_ass");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1280], "stand_clean_weapon");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1312], "stand_brush_pants");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1344], "stand_loose");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1376], "stand_inspect_weapon");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1408], "stand_study_ground");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1440], "stand_walk_look_about");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1472], "stand_throw_grenade");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1504], "stand_lowthrow_grenade");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1536], "stand_close_combat");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1568], "stand_walk_unarmed");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1600], "stand_run_unarmed");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1632], "stand_unarmed");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1664], "running_jump");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1696], "stand_jump_land");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1728], "pick_lock");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1760], "tba_filing_search");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1792], "stand");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1856], "hack_computer");
  strcpy(&WeaponTypeAnim_azBaseAnimName[1824], "none");
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[1896] = &QTask_aaisHandlerSetDirectly[92041];
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[1888], "press_al", 8);
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[1952], "tense_lowerb", 12);
  strcpy(&WeaponTypeAnim_azBaseAnimName[1920], "tense");
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[1964] = (char *)&MTP_atLODVirModel[1].atBoneVertexRefs[18].atVertexRefs[362].iVertex
                                                  + 3;
  strcpy(&WeaponTypeAnim_azBaseAnimName[2016], "stand_run_left");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[2048], "stand_run_ri", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[2060] = (char *)&HumanAI_atMovementQueueItems[786].nNodeID + 3;
  strcpy(&WeaponTypeAnim_azBaseAnimName[1984], "stand_run_forward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2080], "stand_run_forward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2112], "stand_run_forward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2144], "stand_run_backward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2176], "stand_run_backward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2208], "stand_run_backward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2240], "tense_walk_forward");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[2272], "tense_walk_l", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[2284] = (char *)&HumanAI_atMovementQueueItems[776].tNode.ptPrev + 1;
  strcpy(&WeaponTypeAnim_azBaseAnimName[2304], "tense_walk_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2336], "tense_walk_forward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2368], "tense_walk_forward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2400], "tense_walk_backward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2432], "tense_walk_backward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2464], "tense_walk_backward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2496], "fire");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2528], "reload");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[2560], "reload_l", 8);
  strcpy(&WeaponTypeAnim_azBaseAnimName[2592], "reload_finish");
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[2568] = &unk_706F6F;
  strcpy(&WeaponTypeAnim_azBaseAnimName[2624], "tense_look_forward");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[2656], "tense_look_l", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[2668] = (char *)&HumanAI_atMovementQueueItems[776].tNode.ptPrev + 1;
  strcpy(&WeaponTypeAnim_azBaseAnimName[2688], "tense_look_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2720], "tense_look_forward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2752], "tense_look_forward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2784], "tense_look_backward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2816], "tense_look_backward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2848], "tense_look_backward_right");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[2880], "tense_turn_l", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[2892] = (char *)&HumanAI_atMovementQueueItems[776].tNode.ptPrev + 1;
  strcpy(&WeaponTypeAnim_azBaseAnimName[2912], "tense_turn_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2944], "tense_turn_forward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[2976], "tense_turn_forward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3008], "tense_turn_backward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3040], "tense_turn_backward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3072], "tense_turn_backward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3104], "tense_to_stand");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3136], "tense_to_kneel");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3168], "tense_to_flat");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3200], "kneel");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[3232], "kneel_lowerb", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[3244] = (char *)&MTP_atLODVirModel[1].atBoneVertexRefs[18].atVertexRefs[362].iVertex
                                                  + 3;
  strcpy(&WeaponTypeAnim_azBaseAnimName[3264], "kneel_run_forward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3296], "kneel_run_left");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[3328], "kneel_run_ri", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[3340] = (char *)&HumanAI_atMovementQueueItems[786].nNodeID + 3;
  strcpy(&WeaponTypeAnim_azBaseAnimName[3360], "kneel_run_forward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3392], "kneel_run_forward_right");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3424], "kneel_run_backward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3456], "kneel_run_backward_left");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3488], "kneel_run_backward_right");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[3744], "crouch_j", 8);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[3752] = &unk_706D75;
  strcpy(&WeaponTypeAnim_azBaseAnimName[3776], "crouch_jump_land");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[3808], "crouch_t", 8);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[3816] = &QTask_aaisHandlerSetDirectly[157597];
  strcpy(&WeaponTypeAnim_azBaseAnimName[3520], "kneel_fire");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3552], "kneel_reload");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3584], "kneel_roll_right_to_kneel");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3616], "kneel_roll_left_to_kneel");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3648], "kneel_to_stand");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3712], "kneel_to_tense");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3680], "kneel_to_flat");
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[3844] = (char *)&HumanAI_atMovementQueueItems[749].tPosition.vZ + 4;
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[3840] = 1717922156;
  strcpy(&WeaponTypeAnim_azBaseAnimName[3872], "lieflat_fire");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3904], "lieflat_reload");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3936], "lieflat_reload_loop");
  strcpy(&WeaponTypeAnim_azBaseAnimName[3968], "lieflat_reload_finish");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4000], "lieflat_die_headshot");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4064], "lieflat_to_stand");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4096], "crawl");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4128], "crawl");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4160], "crawl");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4192], "crawl");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7520], "lieflat_weaponraise");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7552], "lieflat_weaponraise");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4256], "sit_drive");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4288], "sit_type");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4320], "sit_die");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4352], "climb_ladder");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4384], "get_off_ladder_top");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4416], "get_off_ladder_top");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4448], "slide_ladder");
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[4224] = (char *)&MTP_atLODVirModel[1].atBoneVertexRefs[18].atVertexRefs[872].iVertex
                                                  + 2;
  strcpy(&WeaponTypeAnim_azBaseAnimName[4480], "climb_fence");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4512], "climb_wire");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4544], "slide_wire");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[4032], "lieflat_", 8);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[4040] = &HumanAI_atMovementQueueItems[792].tPosition;
  strcpy(&WeaponTypeAnim_azBaseAnimName[4576], "tense_hit_stomach");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5216], "tense_hit_stomach");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4704], "tense_hit_left_leg");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4832], "tense_hit_right_leg");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4960], "tense_hit_left_arm");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5088], "tense_hit_right_arm");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[4608], "tense_hit_to", 12);
  strcpy(&WeaponTypeAnim_azBaseAnimName[4640], "tense_hit_torso1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4672], "tense_hit_torso2");
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[4620] = &QTask_aaisHandlerSetDirectly[223386];
  strcpy(&WeaponTypeAnim_azBaseAnimName[4736], "tense_hit_left_leg1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4768], "tense_hit_left_leg2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4800], "tense_hit_left_leg2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4864], "tense_hit_right_leg1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4896], "tense_hit_right_leg2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4928], "tense_hit_right_leg3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[4992], "tense_hit_left_arm1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5024], "tense_hit_left_arm2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5056], "tense_hit_left_arm3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5120], "tense_hit_right_arm1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5152], "tense_hit_right_arm2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5184], "tense_hit_right_arm3");
  qmemcpy(&WeaponTypeAnim_azBaseAnimName[5248], "tense_hit_to", 12);
  *(_DWORD *)&WeaponTypeAnim_azBaseAnimName[5260] = &QTask_aaisHandlerSetDirectly[223386];
  strcpy(&WeaponTypeAnim_azBaseAnimName[5280], "tense_hit_torso1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5312], "tense_hit_torso2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5344], "tense_hit_left_leg1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5376], "tense_hit_left_leg2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5408], "tense_hit_left_leg2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5440], "tense_hit_right_leg1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5472], "tense_hit_right_leg2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5504], "tense_hit_right_leg3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5536], "tense_hit_left_arm1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5568], "tense_hit_left_arm2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5600], "tense_hit_left_arm3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5632], "tense_hit_right_arm1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5664], "tense_hit_right_arm2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5696], "tense_hit_right_arm3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5728], "kneel_hit_right_leg");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5760], "kneel_hit_right_leg1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5792], "kneel_hit_right_leg2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5824], "kneel_hit_right_leg3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5856], "kneel_hit_left_leg");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5888], "kneel_hit_left_leg1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5920], "kneel_hit_left_leg2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5952], "kneel_hit_left_leg3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[5984], "lieflat_die_headshot");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6016], "lieflat_die_headshot");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6048], "lieflat_die_normal");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6080], "lieflat_die_normal");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6112], "lieflat_die_front_explosion");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6144], "lieflat_die_back_explosion");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6176], "kneel_die_headshot");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6272], "kneel_die_normal3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6304], "kneel_die_normal4");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6464], "kneel_die_normal3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6208], "kneel_die_normal1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6240], "kneel_die_normal2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6336], "kneel_die_normal1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6368], "kneel_die_normal2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6400], "kneel_die_normal1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6432], "kneel_die_normal2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6496], "kneel_die_normal4");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6528], "kneel_die_normal1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6560], "kneel_die_normal2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6592], "kneel_die_front_explosion");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6624], "kneel_die_front_explosion");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6656], "stand_die_flying");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6688], "stand_die_headshot");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6720], "stand_die_headshot1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6752], "stand_die_headshot2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6784], "stand_die_backshot");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6816], "stand_die_backshot1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6848], "stand_die_backshot2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6880], "stand_die_normal");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6912], "stand_die_normal1");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6944], "stand_die_normal2");
  strcpy(&WeaponTypeAnim_azBaseAnimName[6976], "stand_die_normal3");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7008], "stand_die_normal4");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7040], "stand_die_normal5");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7072], "stand_die_normal7");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7104], "stand_die_normal8");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7136], "stand_die_normal6");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7168], "stand_die_front_explosion");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7200], "stand_die_front_explosion");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7232], "stand_die_back_explosion");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7264], "stand_die_back_explosion");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7296], "death_falling");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7328], "swim");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7360], "swim_backward");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7392], "swim_tread_water");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7424], "swim_death");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7456], "weaponraise");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7488], "weaponraise");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7584], "defusing_bomb");
  strcpy(&WeaponTypeAnim_azBaseAnimName[7616], "tba_silent_kill_guard");
}

// source: j/0/weapons/weapontypeanim.c:468  [size]
unsigned __int16 __cdecl WeaponTypeAnim_GetQTaskType()
{
  return WeaponTypeAnim_eQTaskType;
}

// source: j/0/weapons/weapontypeanim.c:481  [anchor-hash]
void __cdecl WeaponTypeAnim_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("WeaponTypeAnim", 1000, BaseQTaskType, 0, 0);
  WeaponTypeAnim_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, WeaponTypeAnim_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))WeaponTypeAnim_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))WeaponTypeAnim_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponTypeAnim_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponTypeAnim_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v2->nParameters = 0;
  v2->nMaxParameters = 1;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  WeaponTypeAnim_ptParameterList = v2;
  WeaponTypeAnim_InitBaseAnimNameTable();
}

// source: j/0/weapons/weapontypeanim.c:510  [size]
void __cdecl WeaponTypeAnim_Close()
{
  int v0; // esi

  if ( WeaponTypeAnim_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&WeaponTypeAnim_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(WeaponTypeAnim_eQTaskType);
}

// source: j/0/weapons/weapontypeanim.c:530  [anchor-callee]
void __cdecl WeaponTypeAnim_MakeAnimTable(struct QTask_s *ptWeaponTypeAnimQTask, unsigned __int8 *ptHierarchy)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v58; };
    struct { char igi2_o1[4]; unsigned __int8 *v59; };
    struct { char igi2_o2[8]; int *v60; };
    struct { char igi2_o3[24]; char *v61; };
    struct { char igi2_o4[28]; char *i; };
    struct { char igi2_o5[32]; char *p_ptMiddle; };
    struct { char igi2_o6[36]; char v64[99]; };
    struct { char igi2_o7[135]; char v65; };
    struct { char igi2_o8[136]; char Destination[256]; };
    char igi2_extent[392];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // edx
  int v3; // ecx
  char *v4; // eax
  struct QTask_s *v5; // ebp
  char *v6; // edx
  char *v7; // eax
  char v8; // cl
  char *v9; // edi
  char *v11; // eax
  char *v12; // esi
  unsigned int v13; // eax
  char *v14; // edi
  unsigned int nHashTableSize; // ecx
  struct QHashTable_s *v17; // esi
  unsigned int v18; // eax
  int v19; // eax
  int v20; // esi
  int v21; // edx
  int v22; // eax
  int v23; // eax
  char *v24; // eax
  char v25; // cl
  char *v26; // edi
  unsigned int v28; // eax
  char *v29; // edi
  char *v31; // edi
  char *v32; // esi
  char v33; // cl
  struct QHashTable_s *v34; // eax
  unsigned int v35; // ecx
  struct QHashTable_s *v36; // esi
  int v37; // eax
  int v38; // eax
  int v39; // esi
  int v40; // edx
  int v41; // eax
  unsigned int v42; // ecx
  struct QHashTable_s *v43; // esi
  unsigned int v44; // eax
  int v45; // eax
  char *v46; // edi
  int v47; // esi
  int v48; // eax
  int v49; // eax
  int v50; // eax
  unsigned int v51; // ecx
  struct QHashTable_s *v52; // esi
  unsigned int v53; // eax
  int v54; // eax
  int v55; // esi
  int v56; // eax
  int v57; // eax

  ptParent = ptWeaponTypeAnimQTask->ptParent;
  if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, WeaponType_eQTaskType) )
  {
    *(_DWORD *)&ptWeaponTypeAnimQTask[24].eQTaskType = ptHierarchy;
    switch ( (unsigned int)ptParent[16].tQTaskRefList.ptTail )
    {
      case 0u:
        strcpy(igi2_frame.v64, "rifle");
        goto LABEL_15;
      case 1u:
        strcpy(igi2_frame.v64, "pistol");
        goto LABEL_15;
      case 2u:
        v3 = 1953458291;
        v4 = &QTask_aaisHandlerSetDirectly[158351];
        goto LABEL_13;
      case 3u:
        v3 = 1718185579;
        strcpy(&igi2_frame.v64[4], "e");
        goto LABEL_14;
      case 4u:
        v3 = 1852142183;
        v4 = (_BYTE *)(&loc_656460 + 1);
        goto LABEL_13;
      case 5u:
        strcpy(igi2_frame.v64, "binocular");
        goto LABEL_15;
      case 6u:
        strcpy(igi2_frame.v64, "medipack");
        goto LABEL_15;
      case 7u:
        v3 = 1701734765;
        igi2_frame.v64[4] = 0;
        goto LABEL_14;
      case 8u:
        v3 = 1651339106;
        igi2_frame.v64[4] = 0;
        goto LABEL_14;
      case 9u:
        v3 = 1667592307;
        v4 = &QTask_aaisHandlerSetDirectly[22161];
LABEL_13:
        *(_DWORD *)&igi2_frame.v64[4] = v4;
LABEL_14:
        *(_DWORD *)igi2_frame.v64 = v3;
LABEL_15:
        igi2_frame.p_ptMiddle = (char *)&ptParent[10].tQTaskChildren.ptMiddle;
        v5 = ptWeaponTypeAnimQTask + 1;
        v6 = &igi2_frame.Destination[-127845320];
        igi2_frame.v61 = WeaponTypeAnim_azBaseAnimName;
        for ( igi2_frame.i = &igi2_frame.Destination[-127845320]; ; v6 = igi2_frame.i )
        {
          v7 = igi2_frame.v61;
          do
          {
            v8 = *v7;
            v7[(_DWORD)v6] = *v7;
            ++v7;
          }
          while ( v8 );
          v9 = &igi2_frame.v65;
          while ( *++v9 )
            ;
          v11 = igi2_frame.p_ptMiddle;
          *(_WORD *)v9 = 95;
          v12 = v11;
          v13 = strlen(v11) + 1;
          v14 = &igi2_frame.v65;
          while ( *++v14 )
            ;
          qmemcpy(v14, v12, v13);
          strlwr(igi2_frame.Destination);
          nHashTableSize = Hierarchy_ptHashTable->tPrivate.nHashTableSize;
          igi2_frame.v60 = (int *)ptHierarchy;
          igi2_frame.v59 = ptHierarchy;
          igi2_frame.v58 = nHashTableSize;
          v17 = Hierarchy_ptHashTable;
          v18 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(nHashTableSize, ptHierarchy);
          v19 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v17, v18, (const void *)(ptHierarchy));
          v20 = *(_DWORD *)v19;
          v21 = *(_DWORD *)(*(_DWORD *)v19 + 4);
          igi2_frame.v60 = (int *)igi2_frame.Destination;
          v22 = (*(int (__cdecl **)(int, char *))(v20 + 12))(v21, igi2_frame.Destination);
          v23 = (*(int (__cdecl **)(int, int, const void *))(v20 + 28))(v20, v22, (const void *)(igi2_frame.Destination));
          v5->ptNext = (struct QTask_s *)v23;
          if ( !v23 )
          {
            v24 = igi2_frame.v61;
            do
            {
              v25 = *v24;
              v24[(_DWORD)igi2_frame.i] = *v24;
              ++v24;
            }
            while ( v25 );
            v26 = &igi2_frame.v65;
            while ( *++v26 )
              ;
            *(_WORD *)v26 = 95;
            v28 = strlen(igi2_frame.v64) + 1;
            v29 = &igi2_frame.v65;
            while ( *++v29 )
              ;
            qmemcpy(v29, igi2_frame.v64, 4 * (v28 >> 2));
            v32 = &igi2_frame.v64[4 * (v28 >> 2)];
            v31 = &v29[4 * (v28 >> 2)];
            v33 = v28;
            v34 = Hierarchy_ptHashTable;
            qmemcpy(v31, v32, v33 & 3);
            v35 = v34->tPrivate.nHashTableSize;
            igi2_frame.v60 = (int *)ptHierarchy;
            v36 = v34;
            v37 = v34->tPrivate.pfHashFunction(v35, ptHierarchy);
            v38 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v36, v37, (const void *)(ptHierarchy));
            v39 = *(_DWORD *)v38;
            v40 = *(_DWORD *)(*(_DWORD *)v38 + 4);
            igi2_frame.v60 = (int *)igi2_frame.Destination;
            v41 = (*(int (__cdecl **)(int, char *))(v39 + 12))(v40, igi2_frame.Destination);
            v5->ptNext = (struct QTask_s *)(*(int (__cdecl **)(int, int, const void *))(v39 + 28))(v39, v41, (const void *)(igi2_frame.Destination));
          }
          if ( v5->ptNext )
          {
            v46 = igi2_frame.v61;
          }
          else
          {
            v42 = Hierarchy_ptHashTable->tPrivate.nHashTableSize;
            igi2_frame.v60 = (int *)ptHierarchy;
            igi2_frame.v59 = ptHierarchy;
            igi2_frame.v58 = v42;
            v43 = Hierarchy_ptHashTable;
            v44 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(v42, ptHierarchy);
            v45 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v43, v44, (const void *)(ptHierarchy));
            v46 = igi2_frame.v61;
            v47 = *(_DWORD *)v45;
            v48 = *(_DWORD *)(*(_DWORD *)v45 + 4);
            igi2_frame.v60 = (int *)igi2_frame.v61;
            v49 = (*(int (__cdecl **)(int, char *))(v47 + 12))(v48, igi2_frame.v61);
            v50 = (*(int (__cdecl **)(int, int, const void *))(v47 + 28))(v47, v49, (const void *)(igi2_frame.v61));
            v5->ptNext = (struct QTask_s *)v50;
            if ( !v50 )
            {
              v51 = Hierarchy_ptHashTable->tPrivate.nHashTableSize;
              igi2_frame.v60 = (int *)ptHierarchy;
              igi2_frame.v59 = ptHierarchy;
              igi2_frame.v58 = v51;
              v52 = Hierarchy_ptHashTable;
              v53 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(v51, ptHierarchy);
              v54 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v52, v53, (const void *)(ptHierarchy));
              v55 = *(_DWORD *)v54;
              v56 = *(_DWORD *)(*(_DWORD *)v54 + 4);
              igi2_frame.v60 = &dword_68F6C4;
              v57 = (*(int (__cdecl **)(int, int *))(v55 + 12))(v56, &dword_68F6C4);
              v5->ptNext = (struct QTask_s *)(*(int (__cdecl **)(int, int, const void *))(v55 + 28))(v55, v57, (const void *)(&dword_68F6C4));
            }
          }
          v5 = (struct QTask_s *)((char *)v5 + 4);
          igi2_frame.i -= 32;
          igi2_frame.v61 = v46 + 32;
          if ( (int)(v46 + 32) >= 127852968 )
            break;
        }
        break;
      default:
        LDebug_Error("Unknown weapontype %s", (char *)&ptParent[3].eQTaskType);
        abort();
    }
  }
}

// source: j/0/weapons/weapontypeanim.c:645  [size]
struct AnimHeader_s *__cdecl WeaponTypeAnim_GetAnim(
        struct QTask_s *ptWeaponTypeAnimQTask,
        enum WeaponTypeAnim_e eAnim)
{
  return *((struct AnimHeader_s **)&ptWeaponTypeAnimQTask[1].ptNext + eAnim);
}

// source: j/0/weapons/weapontypeanim.c:665  [size]
unsigned __int8 *__cdecl WeaponTypeAnim_GetHierarchy(
        struct QTask_s *ptWeaponTypeAnimQTask)
{
  return *(unsigned __int8 **)&ptWeaponTypeAnimQTask[24].eQTaskType;
}

// source: j/0/weapons/weapontypeanim.c:683  [anchor-callee]
enum WeaponTypeAnim_e __cdecl WeaponTypeAnim_GetWeaponTypeAnimFromName(
        struct QTask_s *ptWeaponTypeAnimQTask,
        char *zName)
{
  enum WeaponTypeAnim_e v2; // edi
  struct QTask_s *i; // ebp

  v2 = WEAPONTYPEANIM_STAND;
  for ( i = ptWeaponTypeAnimQTask + 1;
        !i->ptNext || strcmp((char *)&i->ptNext[1].tQTaskChildren.ptMiddle, zName);
        i = (struct QTask_s *)((char *)i + 4) )
  {
    if ( ++v2 >= WEAPONTYPEANIM_NUM_ANIMS )
      return WEAPONTYPEANIM_STAND;
  }
  return v2;
}
