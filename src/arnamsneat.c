
#include "arnamsneat.h"
#include "defs.h"

static defsAtomic bool gInitialized = false;

void arnamsneatInit(void) {
    if (gInitialized) return;
    gInitialized = true;
}

ARNAMSNEAT_NONNULL() ARNAMSNEAT_RETURNS_NONNULL
ArnamsneatRenderer* arnamsneatCreateRenderer(SDL_Window* window) {
    DEFS_USED(window);
    return (void*) 0x1;
}

void arnamsneatProcessEvents(void) {
    defsAssert(gInitialized);
}

ARNAMSNEAT_NONNULL()
void arnamsneatDestroyRenderer(SDL_Window* window) {
    DEFS_USED(window);
}

void arnamsneatQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}
