/* Additions to the game's menus made from C, beyond what the menu scripts (MENUSYSTEM/*.qvm)
   express: run once per frame from App_Run (overrides/App_Run.c).

   The main menu gets an "openigi.com" item under Quit. It is a MenuText like the script's own
   items, made a child of their window (which lines its children up), with Quit's font, colour
   and alignment, and no On Click script: it shows, and choosing it does nothing. Its text is a
   GLOBAL resource registered here, which is where the menu looks a text resource name up. Menus
   are rebuilt from the scripts at times, so it is added again whenever the window lacks it.

   IGI2_MENU_DUMP=<file> writes the menu tree once (frame 400), for finding things to change. */
#include "igi2.h"
#include <stdio.h>

#define EXTRA_TEXT "openigi.com"

static void Menu_Dump(FILE *f, struct QTask_s *t, int depth)
{
    struct QTask_s *c;
    if (t->eQTaskType == MenuText_eQTaskType) {
        const struct MenuText_t *m = (const struct MenuText_t *)t;
        fprintf(f, "%*sMenuText %p parent %p text '%s' font '%s' colour %ld pos %ld,%ld size %ld,%ld\n",
                depth * 2, "", (void *)t, (void *)t->ptParent, m->zTextResourceName, m->zFontResourceName,
                m->iColour, m->tMenuWindow.nXPos, m->tMenuWindow.nYPos, m->tMenuWindow.nWidth, m->tMenuWindow.nHeight);
    } else {
        fprintf(f, "%*stask %p type %u\n", depth * 2, "", (void *)t, (unsigned)t->eQTaskType);
    }
    for (c = t->tQTaskChildren.ptHead; c && c->ptNext; c = c->ptNext)
        Menu_Dump(f, c, depth + 1);
}

/* the child MenuText of t whose text resource is zName */
static struct MenuText_t *Menu_FindText(struct QTask_s *t, const char *zName)
{
    struct QTask_s *c;
    for (c = t->tQTaskChildren.ptHead; c && c->ptNext; c = c->ptNext)
        if (c->eQTaskType == MenuText_eQTaskType && !strcmp(((struct MenuText_t *)c)->zTextResourceName, zName))
            return (struct MenuText_t *)c;
    return NULL;
}

/* the window holding the main menu's items: the one with "Single Player" and "Quit" */
static struct QTask_s *Menu_FindMainList(struct QTask_s *t)
{
    struct QTask_s *c, *found;
    if (Menu_FindText(t, "Single Player") && Menu_FindText(t, "Quit"))
        return t;
    for (c = t->tQTaskChildren.ptHead; c && c->ptNext; c = c->ptNext)
        if ((found = Menu_FindMainList(c)) != NULL)
            return found;
    return NULL;
}

static void Menu_UpdateInternalData(struct QTask_s *t)
{
    void (__cdecl *pfHandler)(struct QTask_s *, void *) = (void (__cdecl *)(struct QTask_s *, void *))
        QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][t->eQTaskType].pfHandler;
    if (pfHandler)
        pfHandler(t, NULL);
}

static void Menu_AddOpenIgiItem(void)
{
    static int s_isRegistered;
    struct QTask_s *ptList;
    struct MenuText_t *ptQuit, *ptItem;
    if (!MenuManager_ptQTask || !(ptList = Menu_FindMainList(MenuManager_ptQTask)) || Menu_FindText(ptList, EXTRA_TEXT))
        return;
    if (!s_isRegistered) {
        static char s_zText[] = EXTRA_TEXT;
        Resource_Register("GLOBAL:" EXTRA_TEXT, NULL, s_zText, sizeof s_zText, 3u, NULL);
        s_isRegistered = 1;
    }
    ptQuit = Menu_FindText(ptList, "Quit");
    ptItem = (struct MenuText_t *)QTask_NewFn(ptList, MenuText_eQTaskType, ptList);
    if (!ptItem)
        return;
    /* Quit's look and place in the menu, not its script */
    ptItem->tMenuWindow.nXSpacing = ptQuit->tMenuWindow.nXSpacing;
    ptItem->tMenuWindow.nYSpacing = ptQuit->tMenuWindow.nYSpacing;
    ptItem->tMenuWindow.eLineUpMode = ptQuit->tMenuWindow.eLineUpMode;
    ptItem->tMenuWindow.eHorAlignmentMode = ptQuit->tMenuWindow.eHorAlignmentMode;
    ptItem->tMenuWindow.eVertAlignmentMode = ptQuit->tMenuWindow.eVertAlignmentMode;
    ptItem->tMenuWindow.ptMenuManager = ptQuit->tMenuWindow.ptMenuManager;
    strcpy(ptItem->zTextResourceName, EXTRA_TEXT);
    strcpy(ptItem->zFontResourceName, ptQuit->zFontResourceName);
    strcpy(ptItem->zClickSoundResource, ptQuit->zClickSoundResource);
    ptItem->iColour = ptQuit->iColour;
    ptItem->isDimmedWhenDisabled = ptQuit->isDimmedWhenDisabled;
    Menu_UpdateInternalData(&ptItem->tMenuWindow.tQTask);  /* its text, from the font and resource */
    Menu_UpdateInternalData(ptList);                       /* the window lines it up under Quit */
}

void __cdecl Igi2_MenuExtras(void)
{
    static int s_nFrame;
    const char *zDump = getenv("IGI2_MENU_DUMP");
    ++s_nFrame;
    Menu_AddOpenIgiItem();
    if (zDump && *zDump && s_nFrame == 400 && MenuManager_ptQTask) {
        FILE *f = fopen(zDump, "w");
        if (f) {
            Menu_Dump(f, MenuManager_ptQTask, 0);
            fclose(f);
        }
    }
}
