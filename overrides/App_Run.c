// source: app.c:282  [override: the decompiler cannot analyse the _setjmp3 call]
// One frame: run the Flow task's run handler (final-event row 1, indexed by task type) under a
// setjmp guard; a longjmp back here (a fatal error) ends the main loop. The replay driver
// (support/replay.c) feeds the frame's scripted input before it and logs the player after it;
// support/menu_extras.c adds what the menus get from C.
void __cdecl Igi2_ReplayBeforeFrame(void);
void __cdecl Igi2_ReplayAfterFrame(void);
void __cdecl Igi2_MenuExtras(void);

void __cdecl App_Run()
{
  Igi2_ReplayBeforeFrame();
  if ( setjmp(*(jmp_buf *)&App_tLongJumpEnv) )
    Main_isContinue = 0;
  else
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][Flow_ptFlow->tQTask.eQTaskType].pfHandler)(
      (struct QTask_s *)Flow_ptFlow);
  Igi2_MenuExtras();
  Igi2_ReplayAfterFrame();
}
