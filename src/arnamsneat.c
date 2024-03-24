
#include "arnamsneat.h"
#include "defs.h"

static defsAtomic bool gInitialized = false;

void amstInit(void) {
    if (gInitialized) return;
    gInitialized = true;
}

AMST_NONNULL() AMST_RETURNS_NONNULL
AmstRenderer* amstCreateRenderer(SDL_Window* window) {
    DEFS_USED(window);
    return (void*) 0x1;
}

void amstProcessEvents(void) {
    defsAssert(gInitialized);
}

AMST_NONNULL()
void amstDestroyRenderer(SDL_Window* window) {
    DEFS_USED(window);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}
