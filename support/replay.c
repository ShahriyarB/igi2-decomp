/* Replay: drive the game from a script, one simulation tick per frame, and log the player's
   state every frame, so two builds (all retail through the fallback, or our C) can be compared
   line by line and the first frame where they part found without anyone at the keyboard.

   IGI2_REPLAY names the script, IGI2_REPLAY_LOG the log. Script lines, frames counted from start:
     <frame> start                     start the active mission from the menu (menu state 0Eh)
     <from> <to> key <scancode>        hold a key (DirectInput scan code: 39h space, 11h W, ...)
     <from> <to> mouse <dx> <dy>       move the mouse by this much every frame
     <from> <to> button <n>            hold mouse button n (0 left)
     <frame> quit                      write the log and end the process
   Lines starting with # are comments.

   Determinism: the game runs exactly one tick per frame when AppContext_isFixmeSmall is set (its
   "small" developer mode, which also draws a smaller viewport), whatever the clock says. The
   mouse comes from DirectInput even with WinInput: its GetDeviceState is wrapped to report the
   script's movement instead. Keys go into the window-message key table the game copies each tick. */
#include "igi2.h"
#include <stdio.h>

#define REPLAY_MAX 256

void __cdecl Igi2_FallbackSwitch(void);   /* support/fallback.c */

typedef struct {
    int nFrom, nTo;
    int eKind;          /* 0 start, 1 key, 2 mouse, 3 button, 4 quit, 5 switch */
    int a, b;
} ReplayStep;

static ReplayStep s_atStep[REPLAY_MAX];
static int s_nStep = -1;   /* -1: not read yet; 0 after reading: no replay */
static int s_nFrame;
static FILE *s_ptLog;
/* IGI2_REPLAY_DUMP: every frame's player object as raw bytes (frame number, then the
   HumanPlayer_t), so two runs can be compared field by field (tools/replay_fields.py) */
static FILE *s_ptDump;
static int s_nMouseX, s_nMouseY;
static unsigned int s_bButtons;

typedef long (__stdcall *GetDeviceStateFn)(void *pDevice, unsigned long cbData, void *pData);
typedef long (__stdcall *AcquireFn)(void *pDevice);
static GetDeviceStateFn s_pfGetDeviceState;
static unsigned char s_anKey[256];   /* the script's keys, by DirectInput scan code */

/* The game reads DIMOUSESTATE2 (20 bytes: lX, lY, lZ, rgbButtons[8]) from the mouse and 256 key
   bytes from the keyboard: both come from the script. A window in the background cannot acquire
   either device, so Acquire succeeds regardless (Keyboard_Update reads nothing until it does). */
static long __stdcall Replay_GetDeviceState(void *pDevice, unsigned long cbData, void *pData)
{
    if (cbData == 20 && pData) {
        long *pl = (long *)pData;
        unsigned char *pb = (unsigned char *)pData + 12;
        int i;
        pl[0] = s_nMouseX;
        pl[1] = s_nMouseY;
        pl[2] = 0;
        for (i = 0; i < 8; ++i)
            pb[i] = (s_bButtons >> i & 1) ? 0x80 : 0;
        return 0;
    }
    if (cbData == 256 && pData) {
        memcpy(pData, s_anKey, 256);
        return 0;
    }
    return s_pfGetDeviceState(pDevice, cbData, pData);
}

static long __stdcall Replay_Acquire(void *pDevice)
{
    (void)pDevice;
    return 0;
}

/* the mouse and the keyboard are one DirectInput device class: one table serves both */
static void Replay_HookDevices(void)
{
    void **pVtbl;
    DWORD old;
    UINT_PTR pDevice = dword_7089C0 ? (UINT_PTR)dword_7089C0 : (UINT_PTR)Keyboard_lpDIDKeyboard;
    if (s_pfGetDeviceState || !pDevice)
        return;
    pVtbl = *(void ***)pDevice;
    if (!VirtualProtect(&pVtbl[7], 3 * sizeof(void *), PAGE_EXECUTE_READWRITE, &old))
        return;
    s_pfGetDeviceState = (GetDeviceStateFn)pVtbl[9];
    pVtbl[7] = (void *)Replay_Acquire;
    pVtbl[9] = (void *)Replay_GetDeviceState;
    VirtualProtect(&pVtbl[7], 3 * sizeof(void *), old, &old);
}

static void Replay_Read(void)
{
    const char *zScript = getenv("IGI2_REPLAY");
    const char *zLog = getenv("IGI2_REPLAY_LOG");
    char zLine[256], zWhat[32];
    FILE *f;
    s_nStep = 0;
    if (!zScript || !*zScript || !(f = fopen(zScript, "r")))
        return;
    while (fgets(zLine, sizeof zLine, f) && s_nStep < REPLAY_MAX) {
        ReplayStep *s = &s_atStep[s_nStep];
        int nFrom, nTo, a = 0, b = 0;
        if (zLine[0] == '#' || zLine[0] == '\n')
            continue;
        if (sscanf(zLine, "%d %d %31s %i %i", &nFrom, &nTo, zWhat, &a, &b) >= 3) {
            s->nFrom = nFrom;
            s->nTo = nTo;
        } else if (sscanf(zLine, "%d %31s %i", &nFrom, zWhat, &a) >= 2) {
            s->nFrom = s->nTo = nFrom;
        } else {
            continue;
        }
        s->a = a;
        s->b = b;
        if (!strcmp(zWhat, "start")) s->eKind = 0;
        else if (!strcmp(zWhat, "key")) s->eKind = 1;
        else if (!strcmp(zWhat, "mouse")) s->eKind = 2;
        else if (!strcmp(zWhat, "button")) s->eKind = 3;
        else if (!strcmp(zWhat, "quit")) s->eKind = 4;
        else if (!strcmp(zWhat, "switch")) s->eKind = 5;
        else if (!strcmp(zWhat, "restart")) s->eKind = 6;
        else continue;
        ++s_nStep;
    }
    fclose(f);
    if (s_nStep && zLog && *zLog)
        s_ptLog = fopen(zLog, "w");
    {
        const char *zDump = getenv("IGI2_REPLAY_DUMP");
        if (s_nStep && zDump && *zDump)
            s_ptDump = fopen(zDump, "wb");
    }
}

/* before the frame: this frame's input */
void __cdecl Igi2_ReplayBeforeFrame(void)
{
    int i;
    if (s_nStep < 0)
        Replay_Read();
    if (!s_nStep)
        return;
    AppContext_isFixmeSmall = 1;
    Replay_HookDevices();
    s_nMouseX = s_nMouseY = 0;
    s_bButtons = 0;
    memset(s_anKey, 0, sizeof s_anKey);
    for (i = 0; i < s_nStep; ++i) {
        const ReplayStep *s = &s_atStep[i];
        int isOn = s_nFrame >= s->nFrom && s_nFrame <= s->nTo;
        switch (s->eKind) {
        case 0:
            if (s_nFrame == s->nFrom && MenuManager_ptQTask) {
                Game_iMissionID = s->a ? s->a : 11;  /* what picking a mission in the menu sets */
                MenuManager_ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)0xE;
            }
            break;
        case 1:
            if (isOn && s->a > 0 && s->a < 256)
                s_anKey[s->a] = 0x80;
            break;
        case 2:
            if (isOn) {
                s_nMouseX += s->a;
                s_nMouseY += s->b;
            }
            break;
        case 3:
            if (isOn)
                s_bButtons |= 1u << (s->a & 7);
            break;
        case 6:
            if (s_nFrame == s->nFrom && Flow_ptFlow)
                Flow_ptFlow->eRequestedEvent = 5;  /* FLOW_EVENT_RESTART_GAME */
            break;
        case 5:
#ifdef IGI2_FALLBACK
            if (s_nFrame == s->nFrom)
                Igi2_FallbackSwitch();
#endif
            break;
        case 4:
            if (s_nFrame == s->nFrom) {
                if (s_ptLog)
                    fclose(s_ptLog);
                if (s_ptDump)
                    fclose(s_ptDump);
                ExitProcess(0);
            }
            break;
        }
    }
    /* WinInput reads keys from the window-message table instead of the device: same keys there */
    memcpy(Keyboard_anWindowsCurrentKey, s_anKey, sizeof s_anKey);
}

/* IGI2_PROBE=vertex: call our Terrain_VertexFunction and the retail one (0x585D10, which only
   reads terrain data) on the same points around the player, and log where they disagree. The
   retail code is made runnable for it (a C build otherwise never executes it). */
typedef void (__cdecl *VertexFn)(float *, struct real32x3_t *, unsigned int *, unsigned __int8 *, unsigned __int8 *,
                                 float, float, float);

static void Replay_ProbeVertex(const struct real64x3_t *p)
{
    static int s_isRunnable, s_nLogged;
    VertexFn pfRetail = (VertexFn)(UINT_PTR)0x585D10u;
    int dx, dy;
    if (!s_isRunnable) {
        DWORD old;
        VirtualProtect((void *)(UINT_PTR)0x401000u, 0x2A0000u, PAGE_EXECUTE_READWRITE, &old);
        s_isRunnable = 1;
    }
    for (dy = -2; dy <= 2 && s_nLogged < 40; ++dy) {
        for (dx = -2; dx <= 2 && s_nLogged < 40; ++dx) {
            float vX = (float)(p->vX + dx * 37.0), vY = (float)(p->vY + dy * 37.0);
            float zA = 0, zB = 0;
            struct real32x3_t nA = {0}, nB = {0};
            unsigned int cA = 0, cB = 0;
            unsigned __int8 mA = 0, mB = 0, lA = 0, lB = 0;
            Terrain_VertexFunction(&zA, &nA, &cA, &mA, &lA, vX, vY, 0.0f);
            pfRetail(&zB, &nB, &cB, &mB, &lB, vX, vY, 0.0f);
            if (memcmp(&zA, &zB, 4) || memcmp(&nA, &nB, sizeof nA) || mA != mB || lA != lB) {
                fprintf(s_ptLog, "probe vertex x %.9g (%08x) y %.9g (%08x): z %08x/%08x n %08x %08x %08x / %08x %08x %08x\n",
                        vX, *(unsigned int *)&vX, vY, *(unsigned int *)&vY, *(unsigned int *)&zA, *(unsigned int *)&zB,
                        *(unsigned int *)&nA.vX, *(unsigned int *)&nA.vY, *(unsigned int *)&nA.vZ,
                        *(unsigned int *)&nB.vX, *(unsigned int *)&nB.vY, *(unsigned int *)&nB.vZ);
                ++s_nLogged;
            }
        }
    }
}

/* after the frame: the player's state */
void __cdecl Igi2_ReplayAfterFrame(void)
{
    struct QTask_s *ptPlayer;
    if (s_nStep <= 0)
        return;
    ++s_nFrame;
    if (!s_ptLog)
        return;
    if (!Game_ptGame || !(ptPlayer = Game_GetPlayerQTask(0))) {
        if (s_nFrame % 30 == 0)
            fprintf(s_ptLog, "%d - event %d menu %d\n", s_nFrame, Flow_ptFlow ? (int)Flow_ptFlow->eCurrentEvent : -1,
                    MenuManager_ptQTask ? (int)(UINT_PTR)MenuManager_ptQTask[1].tQTaskChildren.ptMiddle : -1);
        fflush(s_ptLog);
        return;
    }
    {
        const struct Human_s *h = (const struct Human_s *)ptPlayer;
        const struct real64x3_t *p = (const struct real64x3_t *)&ptPlayer[1];
        fprintf(s_ptLog,
                "%d %d pos %.17g %.17g %.17g spd %.9g %.9g %.9g tot %.9g %.9g %.9g pose %d gnd %d dist %.17g "
                "state %d %d anim %ld %ld\n",
                s_nFrame, Flow_ptFlow ? Flow_ptFlow->nTicks : -1, p->vX, p->vY, p->vZ,
                h->tSpeed.vX, h->tSpeed.vY, h->tSpeed.vZ, h->tTotalSpeed.vX, h->tTotalSpeed.vY, h->tTotalSpeed.vZ,
                h->ePose, h->isGroundCollision, h->vDistanceToGround, h->tState.nState, h->tState.nPreviousState,
                h->tHumanAnim.iStateLastUsedToSetMainAnimation, h->tHumanAnim.iStateLastUsedToSetUpperBodyAnimation);
        if (getenv("IGI2_PROBE") && !strcmp(getenv("IGI2_PROBE"), "vertex"))
            Replay_ProbeVertex(p);
        if (s_ptDump) {
            fwrite(&s_nFrame, sizeof s_nFrame, 1, s_ptDump);
            fwrite(ptPlayer, sizeof(struct HumanPlayer_t), 1, s_ptDump);
        }
    }
}
