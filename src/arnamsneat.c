
#include "arnamsneat.h"
#include "defs.h"

static defsAtomic bool gInitialized = false;

void amstInit(void) {
    if (gInitialized) return;
    gInitialized = true;
}

AmstRenderer* AMST_NULLABLE amstCreateRenderer(SDL_Window* AMST_NONNULL window) {
    DEFS_USED(window);
    return (void*) 0x1;
}

void amstProcessEvents(void) {
    defsAssert(gInitialized);
}

void amstDestroyRenderer(SDL_Window* AMST_NONNULL window) {
    DEFS_USED(window);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}
