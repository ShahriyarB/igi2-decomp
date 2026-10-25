/* f/f.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/f.c:33  [anchor-hash]
void __cdecl F_Open()
{
  D_Open();
  E3_Open();
  SoundSys_Open();
  SoundDefBase_Open();
  Microphone_Open();
  SoundDefGroup_Open();
  SoundDefSound_Open();
  SoundDefGraph_Open();
  SoundDefTriggerOnce_Open();
  Screen_Open();
  ViewportQTask_Open();
  FreeCameraQTask_Open();
  Resource_Register("LOCAL:debug.fnt", nullptr, DebugText_anFont, 0x507Cu, 3u, nullptr);
  FadeOut_Open();
  ParticleSystem_Open();
  SpriteParticle_eQTaskType = QTask_NewQTaskType("SpriteParticleSystemDynCubeObj", 224, ParticleSystem_eQTaskType, 0, 0);
  SpriteParticle_isInitialised = 1;
  FlashQTask_Open();
  Filter_Open();
}

// source: f/f.c:67  [layout]
void __cdecl F_Close()
{
  Filter_Close();
  QTask_DeleteQTaskType(FlashQTask_eQTaskType);
  FlashQTask_isInitialised[0] = 0;
  QTask_DeleteQTaskType(SpriteParticle_eQTaskType);
  SpriteParticle_isInitialised = 0;
  QTask_DeleteQTaskType(ParticleSystem_eQTaskType);
  QTask_DeleteQTaskType(FadeOut_eFadeOutStartQTaskType);
  QTask_DeleteQTaskType(FadeOut_eFadeOutEndQTaskType);
  QTask_DeleteQTaskType(FreeCameraQTask_eQTaskType);
  ViewportQTask_Close();
  QTask_DeleteQTaskEventNoContext(Screen_eDrawQTaskEvent);
  Screen_eDrawQTaskEvent = 512;
  QTask_DeleteQTaskType(Screen_eQTaskType);
  Screen_isInitialised = 0;
  QTask_DeleteQTaskType(SoundDefTriggerOnce_eQTaskType);
  SoundDefTriggerOnce_eQTaskType = 512;
  SoundDefTriggerOnce_eCreateQTaskType = 512;
  QTask_DeleteQTaskType(SoundDefGraph_eQTaskType);
  SoundDefGraph_eQTaskType = 512;
  SoundDefGraph_eCreateQTaskType = 512;
  QTask_DeleteQTaskType(SoundDefSound_eQTaskType);
  SoundDefSound_eQTaskType = 512;
  SoundDefSound_eCreateQTaskType = 512;
  QTask_DeleteQTaskType(SoundDefGroup_eQTaskType);
  SoundDefGroup_eQTaskType = 512;
  SoundDefGroup_eCreateQTaskType = 512;
  QTask_DeleteQTaskEvent(Microphone_eTriggerEvent);
  QTask_DeleteQTaskType(Microphone_eQTaskType);
  QTask_DeleteQTaskType(SoundDefBase_eQTaskType);
  SoundSys_Close();
  E3_Close();
  D_Close();
}
